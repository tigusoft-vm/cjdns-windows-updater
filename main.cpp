#include "c_http_downloader.hpp"
#include "c_updater.hpp"
#include "c_cjdns_updater.hpp"
#include "c_tiguup_updater.hpp"


#include <iostream>
#include <fstream>
#include <stdexcept>

int main() {
/*	std::ofstream ofs("out");
	c_http_downloader downloader;
	downloader.download_file("127.0.0.1/index.html", ofs);
	c_updater updater;
	updater.update();*/
	
	c_cjdns_updater cjnds_updater("fc72:aa65:c5c2:4a2d:54e:7947:b671:e00c", std::unique_ptr<i_downloader>(new c_http_downloader));
	try {
		cjnds_updater.update();
	}
	catch(const std::exception &e) {
		std::cout << "exception: " << e.what() << std::endl;
	}

/*	DWORD test = 481516;
	try {
		win_utility::c_windows_reg::set_register_value(
			HKEY_LOCAL_MACHINE,
			R"(SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\test)",
			"test_key",
			REG_DWORD,
			(const BYTE *)&test,
			sizeof(test));
	}
	catch(const std::runtime_error &e){
		std::cout << "exception " << e.what() << std::endl;
	}
*/
    return 0;
}
