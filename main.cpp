#include "c_http_downloader.hpp"
#include <iostream>
#include "c_sha512_ext.hpp"
#include "c_updater.hpp"

bool sha512test(const std::string msg) {

    std::string hash = c_sha512_ext::generate_hash(msg);

    std::cout << "sha512 test:\n";
    std::cout << "msg: " << msg << "\nsha512: " << hash << std::endl;
    std::cout << "verifying . . .\n";
    if(c_sha512_ext::verify_hash(msg,hash)) {
        std::cout << "OK";
        return 0;
    } else {
        std::cout << "BAD SUM";
        return 1;
    }
}

int main() {
	//c_http_downloader downloader;
	//downloader.download_file("127.0.0.1/index.html", "out");
	c_updater updater;
	updater.update();

	sha512test("test");
    return 0;
}
