#if defined _WIN32 || defined __CYGWIN__

#include "c_windows_service.hpp"
#include "c_windows_utility.hpp"
#include <chrono>
#include <stdexcept>
#include <thread>
#include <windows.h>
#include <winsvc.h>

#ifdef __CYGWIN__
#include <sstream>
namespace std {
template <typename T>
std::string to_string(T val) {
    std::stringstream stream;
    stream << val;
    return stream.str();
}
} // namespace std
#endif

namespace win_utility {
	
void c_windows_service::stop_service(const std::string &service_name) {
	SetLastError(ERROR_SUCCESS);
	if (!c_windows_utility::is_user_admin())
		throw std::runtime_error("required administrator permissions");
	SC_HANDLE SCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
	if (GetLastError() == ERROR_ACCESS_DENIED) {
		throw std::runtime_error("ERROR_ACCESS_DENIED");
	}
	SC_HANDLE SHandle = OpenService(SCManager, service_name.c_str(), SC_MANAGER_ALL_ACCESS);
	if (SHandle == nullptr) {
		throw std::runtime_error("open service error");
	}

	SERVICE_STATUS status;
	if (!ControlService(SHandle, SERVICE_CONTROL_STOP, &status)) {
		throw std::runtime_error("fail to send stop service command");
	}

	// wait for service end
	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		QueryServiceStatus(SHandle, &status);
	}
	while(status.dwCurrentState != SERVICE_STOPPED);

	CloseServiceHandle(SCManager);
	CloseServiceHandle(SHandle);

	if (GetLastError()) {
		throw std::runtime_error(std::string("last error (GetLastError()) ") + std::to_string(GetLastError()));
	}
}

void c_windows_service::start_service(const std::string &service_name) {
	SetLastError(ERROR_SUCCESS);
	if (!c_windows_utility::is_user_admin())
		throw std::runtime_error("required administrator permissions");
	SC_HANDLE SCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
	if (GetLastError() == ERROR_ACCESS_DENIED) {
		throw std::runtime_error("ERROR_ACCESS_DENIED");
	}
	SC_HANDLE SHandle = OpenService(SCManager, service_name.c_str(), SC_MANAGER_ALL_ACCESS);
	if (SHandle == nullptr) {
		throw std::runtime_error("open service error");
	}

	if(!StartService(SHandle, 0, nullptr)) {
		throw std::runtime_error("start service error");
	}

	CloseServiceHandle(SCManager);
	CloseServiceHandle(SHandle);

	if (GetLastError()) {
		throw std::runtime_error(std::string("last error (GetLastError()) ") + std::to_string(GetLastError()));
	}
}
	
} // namespace


#endif