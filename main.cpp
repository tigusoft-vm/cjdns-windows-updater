#include "c_http_downloader.hpp"
#include "c_updater.hpp"
#include <iostream>

int main() {
	c_http_downloader downloader;
	downloader.download_file("127.0.0.1/index.html", "out");
    return 0;
}
