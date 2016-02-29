#include "c_tiguup_updater.hpp"
#include "../win-utility-lib/c_windows_reg.hpp"

#include <iostream> // XXX
#include <sstream>

c_tiguup_updater::c_tiguup_updater(const std::string &server_address, std::unique_ptr<i_downloader> &&downloader) :
	c_updater(server_address, std::move(downloader))
{
}

void c_tiguup_updater::update() {
	std::cout << "updater local version: " << get_local_version() << std::endl;
	std::cout << "updater remote version: " << get_remote_version() << std::endl;
}

// updater version saved in HKEY_LOCAL_MACHINE\SOFTWARE\cjdns in updater-ver
unsigned int c_tiguup_updater::get_local_version() {
	std::string ver(
		win_utility::c_windows_reg::get_register_value(HKEY_LOCAL_MACHINE, R"(SOFTWARE\cjdns)", "updater-ver") 
	);
	unsigned int ret_ver = *reinterpret_cast<const DWORD*>(ver.data());
	return ret_ver;
}

unsigned int c_tiguup_updater::get_remote_version() {
	std::ostringstream oss;
	m_downloader->download_file(m_server_address + "/ver-updater", oss);
	return get_version_number(std::move(oss.str()));
}
