#include "c_http_downloader.hpp"
#include <iostream>
#include "c_sha512_ext.hpp"

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
    c_http_downloader downloader;
    downloader.download_file("fc72:aa65:c5c2:4a2d:54e:7947:b671:e00c/index.html", "out");

    sha512test("test");

    return 0;
}



