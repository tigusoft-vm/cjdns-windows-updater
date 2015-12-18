#include "c_url_downloader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

void c_url_downloader::download_file (const std::string &file_address, const std::string &out_path) {
	using namespace boost::asio;

	io_service io_servise;
	ip::tcp::resolver::iterator endpoint_iterator;
	try {
		ip::tcp::resolver resolver(io_servise);
		ip::tcp::resolver::query query(file_address, "http");
		endpoint_iterator = resolver.resolve(query);
		ip::tcp::socket socket = ip::tcp::socket(io_servise);
		boost::asio::connect(socket, resolver.resolve(query));

	}
	catch(boost::system::system_error& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		return;
	}


	std::ofstream out_file(out_path); // TODO save data to file
}

std::string c_url_downloader::generate_request(const std::string &hostname, const std::string &path) {
	std::ostringstream oss;
	oss
		<< "GET " << path << " HTTP/1.1\r\n"
		<< "Host: " << hostname << "\r\n"
		<< "Connection: close" << "\r\n"
		<< "\r\n";
	return oss.str();
}
