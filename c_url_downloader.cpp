#include "c_url_downloader.hpp"
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

void c_url_downloader::download_file (const std::string &file_address, const std::string &out_path)
{
	using namespace boost::asio;

	io_service io_servise;
	ip::tcp::resolver::iterator endpoint_iterator;
	try {
		ip::tcp::resolver resolver(io_servise);
		ip::tcp::resolver::query query(file_address, "http");
		endpoint_iterator = resolver.resolve(query);
	}
	catch(boost::system::system_error& error) {
		std::cerr << "Resolver error: " << error.what() << std::endl;
		return;
	}

	ip::tcp::socket socket(io_service);


	std::ofstream out_file(out_path); // TODO
}
