#include "c_url_downloader.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

void c_url_downloader::download_file(const std::string &file_address, const std::string &out_path) {
	using namespace boost::asio;

	io_service io_servise;
	ip::tcp::resolver::iterator endpoint_iterator;
	try {
		ip::tcp::resolver resolver(io_servise);
		ip::tcp::resolver::query query(file_address, "http");
		endpoint_iterator = resolver.resolve(query);
		ip::tcp::socket socket = ip::tcp::socket(io_servise);
		boost::asio::connect(socket, resolver.resolve(query));

// 		const std::string request = generate_request("127.0.0.1", "cjdroute.exe");
		const std::string request = generate_request("127.0.0.1", "index.html"); // TODO parse
		socket.write_some(boost::asio::buffer(request));

		// read data
		boost::system::error_code ec;
		std::ofstream out_file(out_path, std::ios::out | std::ios::binary);
		do {
			std::array<char, 1024> buffer;
			size_t bytesRead = socket.read_some(boost::asio::buffer(buffer), ec);
			//std::cout << "read " << bytesRead << " bytes" << std::endl;
			out_file.write(buffer.data(), bytesRead);
// 			for (size_t i = 0; i < bytesRead; ++i)
// 				std::cout << buffer[i];
// 			std::cout << std::endl;
		}
		while (!ec);

	}
	catch(boost::system::system_error& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		return;
	}

}

std::string c_url_downloader::generate_request(const std::string &hostname, const std::string &path) {
	std::ostringstream oss;
	oss
		<< "GET /" << path << "\r\n"
		<< "Host: " << hostname << "\r\n"
		<< "Accept: */*\r\n"
		<< "Connection: close" << "\r\n"
		<< "\r\n";
	return oss.str();
}
