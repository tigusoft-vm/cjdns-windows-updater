#include "c_cjdns_updater.hpp"

#include <chrono>
#include <exception>
#include <iostream>
#include <thread>

void c_cjdns_updater::update() {
	//std::cout << get_register_value(HKEY_LOCAL_MACHINE, R"(SYSTEM\ControlSet001\services\cjdns)", "ImagePath") << std::endl;
	//stop_cjdns_service();
	//start_cjdns_service();
	get_cjdns_install_path();
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

void c_cjdns_updater::start_cjdns_service() {
	SC_HANDLE SCManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
	if (GetLastError() == ERROR_ACCESS_DENIED) {
		throw std::runtime_error("ERROR_ACCESS_DENIED");
	}
	SC_HANDLE SHandle = OpenService(SCManager, m_service_name.c_str(), SC_MANAGER_ALL_ACCESS);
	if (SHandle == nullptr) {
		throw std::runtime_error("open service error");
	}

	if(!StartService(SHandle, 0, nullptr)) {
		throw std::runtime_error("start service error");
	}

	CloseServiceHandle(SCManager);
	CloseServiceHandle(SHandle);
}

std::string c_cjdns_updater::get_cjdns_install_path() {
	std::string path = get_register_value(HKEY_LOCAL_MACHINE, R"(SYSTEM\ControlSet001\services\cjdns)", "ImagePath");
	size_t pos = path.find_last_of('\\');
	path.erase(pos);
	return path;
}

std::string c_cjdns_updater::get_register_value(HKEY root, const std::string &key, const std::string &name) {
	HKEY hKey;
	if (RegOpenKeyEx(root, key.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
		throw std::runtime_error("could not open registry key");
	}
	DWORD type = 0;
	DWORD cbData = 0;
	if (RegQueryValueEx(hKey, name.c_str(), nullptr, &type, nullptr, &cbData) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		throw std::runtime_error("Could not read registry value");
	}

	std::string value(cbData, '\0');
	if (RegQueryValueEx(hKey, name.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(&value[0]), &cbData) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		throw "Could not read registry value";
	}

	RegCloseKey(hKey);
	return value;
}