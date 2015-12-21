#include "c_updater.hpp"
#include "c_http_downloader.hpp"

#include <fstream>
#include <iostream>

c_updater::c_updater() :
	m_downloader(new c_http_downloader)
{
}

void c_updater::update() {
	// load file
	const std::string file_path("test.txt"); // TODO filename
	std::ifstream file(file_path, std::ios::binary | std::ios::ate);
	size_t file_size =  file.tellg();
	file.close();
	std::cout << "file_size: " << file_size << std::endl;

	std::string binary_data_from_file;
	binary_data_from_file.reserve(file_size);

	file.open(file_path, std::ios::binary | std::ios::in);
	file.read(&binary_data_from_file[0], file_size);
}
