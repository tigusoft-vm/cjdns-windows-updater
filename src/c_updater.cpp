#include "c_updater.hpp"
#include "c_http_downloader.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

c_updater::c_updater() :
	m_downloader(new c_http_downloader)
{
}

void c_updater::update() {
// 	// load file
// 	const std::string file_path("test.txt"); // TODO filename
// 	std::ifstream file(file_path, std::ios::binary | std::ios::ate);
// 	size_t file_size =  file.tellg();
// 	file.close();
// 	std::cout << "file_size: " << file_size << std::endl;
//
// 	std::string binary_data_from_file;
// 	binary_data_from_file.reserve(file_size);
//
// 	file.open(file_path, std::ios::binary | std::ios::in);
// 	file.read(&binary_data_from_file[0], file_size);

	get_remote_version();
}

/*
 * For server file: 17.1-1 returns 1711
 */
unsigned int c_updater::get_remote_version() {
	std::ostringstream oss;
	m_downloader->download_file("127.0.0.1/ver", oss); // TODO server address
	std::string ver_str(oss.str());
	std::string::iterator it = ver_str.begin();
	while (it < ver_str.end()) {
		if (!std::isdigit(*it)) {
			ver_str.erase(it);
			continue;
		}
		it++;
	}
	unsigned int version_number = std::stoul(ver_str);
	return version_number;
}
