#include "c_cjdns_updater.hpp"

#include <chrono>
#include <exception>
#include <thread>

void c_cjdns_updater::update() {
	stop_cjdns_service();
}

void c_cjdns_updater::stop_cjdns_service() {
	SC_HANDLE SCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
	if (GetLastError() == ERROR_ACCESS_DENIED) {
		throw std::runtime_error("ERROR_ACCESS_DENIED");
	}
	SC_HANDLE SHandle = OpenService(SCManager, m_service_name.c_str(), SC_MANAGER_ALL_ACCESS);
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