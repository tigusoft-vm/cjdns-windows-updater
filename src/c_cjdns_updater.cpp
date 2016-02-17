#include "c_cjdns_updater.hpp"

#include <boost/filesystem.hpp>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <thread>

void c_cjdns_updater::update() {
	get_local_version();
	/*const size_t file_size = 1024*1024*5; // 5 MB
	std::string filename("tmp_file");
	std::ofstream downloaded_file(filename.c_str());
	downloaded_file.close();
	boost::filesystem::resize_file(filename, file_size);
	downloaded_file.open(filename.c_str(), std::ios::app);
	m_downloader->download_file("fc72:aa65:c5c2:4a2d:54e:7947:b671:e00c/cjdroute.exe", downloaded_file);

	std::string path = get_cjdns_install_path();
	stop_cjdns_service();
	boost::filesystem::rename(path + "\\cjdroute.exe", path + "\\cjdroute-old.exe");
	boost::filesystem::rename(filename, path + "\\cjdroute.exe");
	start_cjdns_service();*/
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

unsigned int c_cjdns_updater::get_local_version() {
	std::string current_version = get_register_value(
		HKEY_LOCAL_MACHINE,
		R"(SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\cjdns)",
		"DisplayVersion");
		std::cout << "current version: " << current_version << std::endl;
	return 0; // TODO
}