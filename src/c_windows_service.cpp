#if defined _WIN32 || defined __CYGWIN__

#include "c_windows_service.hpp"
#include <chrono>
#include <stdexcept>
#include <thread>
#include <windows.h>
#include <winsvc.h>

namespace win_utility {
	
void c_windows_service::stop_cjdns_service(const std::string &service_name) {
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

	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		QueryServiceStatus(SHandle, &status);
	}
	while(status.dwCurrentState != SERVICE_STOPPED);

	CloseServiceHandle(SCManager);
	CloseServiceHandle(SHandle);
}

void c_windows_service::start_cjdns_service(const std::string &service_name) {
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
}
	
} // namespace


#endif