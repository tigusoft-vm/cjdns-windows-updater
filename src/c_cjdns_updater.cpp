#include "c_cjdns_updater.hpp"
#include "../win-utility-lib/c_windows_reg.hpp"
#include "../win-utility-lib/c_windows_service.hpp"

#include <boost/filesystem.hpp>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

c_cjdns_updater::c_cjdns_updater(const std::string &server_address, std::unique_ptr<i_downloader> &&downloader) :
	c_updater(server_address, std::move(downloader))
{
}

void c_cjdns_updater::update() {
	const unsigned int local_version = get_local_version();
	const unsigned int remote_version = get_remote_version();
	std::cout << "local version " << local_version << std::endl;
	std::cout << "remote version " << remote_version << std::endl;
	std::cout << "cjdns install path: " << get_cjdns_install_path()	<< std::endl;
	if (local_version < remote_version) return;
	/*const size_t file_size = 1024*1024*5; // 5 MB
	std::string filename("tmp_file");
	std::ofstream downloaded_file(filename.c_str());
	downloaded_file.close();
	boost::filesystem::resize_file(filename, file_size);
	downloaded_file.open(filename.c_str(), std::ios::app);
	m_downloader->download_file(m_server_address + "/cjdroute.exe", downloaded_file);

	std::string path = get_cjdns_install_path();
	win_utility::c_windows_service::stop_service(m_service_name);
	boost::filesystem::rename(path + "\\cjdroute.exe", path + "\\cjdroute-old.exe");
	boost::filesystem::rename(filename, path + "\\cjdroute.exe");
	win_utility::c_windows_service::start_service(m_service_name);*/
}

std::string c_cjdns_updater::get_cjdns_install_path() {
	std::string path = win_utility::c_windows_reg::get_register_value(HKEY_LOCAL_MACHINE, R"(SYSTEM\ControlSet001\services\cjdns)", "ImagePath");
	size_t pos = path.find_last_of('\\');
	path.erase(pos);
	return path;
}

unsigned int c_cjdns_updater::get_remote_version() {
	std::ostringstream oss;
	m_downloader->download_file(m_server_address + "/ver", oss); // TODO filename on server
	return get_version_number(std::move(oss.str()));
}

unsigned int c_cjdns_updater::get_local_version() {
	std::string current_version_str = win_utility::c_windows_reg::get_register_value(
		HKEY_LOCAL_MACHINE,
		R"(SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\cjdns)",
		"DisplayVersion");
	return get_version_number(std::move(current_version_str));
}