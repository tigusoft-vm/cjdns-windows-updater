#include "c_http_downloader.hpp"
#include <array>
#include <ostream>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

void c_http_downloader::download_file(const std::string &file_address, std::ostream &out_stream) {
	auto it = file_address.begin();
	std::string host_name;

	while (*it != '/') {
		host_name.push_back(*it);
		it++;
		if (it == file_address.end()) {
			throw std::invalid_argument("Invalid path");
		}
	}

	std::string file_path(it, file_address.end());

	using namespace boost::asio;
	io_service io_servise;
	ip::tcp::resolver::iterator endpoint_iterator;
	ip::tcp::resolver resolver(io_servise);
	ip::tcp::resolver::query query(host_name, "http");
	endpoint_iterator = resolver.resolve(query);
	ip::tcp::socket socket = ip::tcp::socket(io_servise);
	boost::asio::connect(socket, resolver.resolve(query));

	const std::string request = generate_request(host_name, file_path);
	socket.write_some(boost::asio::buffer(request));

	// read data
	boost::system::error_code ec;
	do {
		std::array<char, 1024> buffer;
		size_t bytesRead = socket.read_some(boost::asio::buffer(buffer), ec);
		out_stream.write(buffer.data(), bytesRead);
	}
	while (!ec);
}

std::string c_http_downloader::generate_request(const std::string &hostname, const std::string &path) {
	std::ostringstream oss;
	oss
		<< "GET " << path << "\r\n"
		<< "Host: " << hostname << "\r\n"
		<< "Accept: */*\r\n"
		<< "Connection: close" << "\r\n"
		<< "\r\n";
	return oss.str();
}
