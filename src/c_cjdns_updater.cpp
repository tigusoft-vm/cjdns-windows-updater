#include "c_cjdns_updater.hpp"
#include "c_windows_reg.hpp"
#include "c_windows_service.hpp"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <thread>


#ifdef __CYGWIN__
namespace std {
unsigned int stol(const std::string &str); // source in c_updater.cpp
} // namespace std
#endif



void c_cjdns_updater::update() {
	std::cout << "local version " << get_local_version() << std::endl;
	std::cout << "cjdns install path: " << get_cjdns_install_path()	<< std::endl;
	/*const size_t file_size = 1024*1024*5; // 5 MB
	std::string filename("tmp_file");
	std::ofstream downloaded_file(filename.c_str());
	downloaded_file.close();
	boost::filesystem::resize_file(filename, file_size);
	downloaded_file.open(filename.c_str(), std::ios::app);
	m_downloader->download_file("fc72:aa65:c5c2:4a2d:54e:7947:b671:e00c/cjdroute.exe", downloaded_file);

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

unsigned int c_cjdns_updater::get_local_version() {
	std::string current_version_str = win_utility::c_windows_reg::get_register_value(
		HKEY_LOCAL_MACHINE,
		R"(SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\cjdns)",
		"DisplayVersion");
	auto new_end = std::remove_if(current_version_str.begin(), current_version_str.end(), [](char c){return !std::isdigit(c);});
	current_version_str.erase(new_end, current_version_str.end());
	return std::stol(current_version_str);
}