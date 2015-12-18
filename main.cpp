#include "c_http_downloader.hpp"
#include <iostream>

int main() {
	c_http_downloader downloader;
	downloader.download_file("127.0.0.1", "out");
    return 0;
}
