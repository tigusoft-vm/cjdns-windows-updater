#include "c_http_downloader.hpp"
#include "c_updater.hpp"

#include <iostream>
#include <fstream>

int main() {
	std::ofstream ofs("out");
	c_http_downloader downloader;
	downloader.download_file("127.0.0.1/index.html", ofs);
	c_updater updater;
	updater.update();

    return 0;
}
