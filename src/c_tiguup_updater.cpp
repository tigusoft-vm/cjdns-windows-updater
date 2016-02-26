#include "c_tiguup_updater.hpp"
#include "../win-utility-lib/c_windows_reg.hpp"

#include <iostream> // XXX

c_tiguup_updater::c_tiguup_updater() {
	std::cout << get_local_version() << std::endl;
}

void c_tiguup_updater::update() {
	
}

// updater version saved in HKEY_LOCAL_MACHINE\SOFTWARE\cjdns in updater-ver
unsigned int c_tiguup_updater::get_local_version() {
	std::string ver(
		win_utility::c_windows_reg::get_register_value(HKEY_LOCAL_MACHINE, R"(SOFTWARE\cjdns)", "updater-ver") 
	);
	unsigned int ret_ver = *reinterpret_cast<const DWORD*>(ver.data());
	return ret_ver;
}