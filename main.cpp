#include "c_http_downloader.hpp"
#include "c_updater.hpp"
#include "c_cjdns_updater.hpp"

#include <iostream>
#include <fstream>

int main() {
/*	std::ofstream ofs("out");
	c_http_downloader downloader;
	downloader.download_file("127.0.0.1/index.html", ofs);
	c_updater updater;
	updater.update();*/
	c_cjdns_updater cjnds_updater;
	try {
		cjnds_updater.update();
	}
	catch(const std::exception &e) {
		std::cout << "exception: " << e.what() << std::endl;
	}

    return 0;
}
