#include "c_url_downloader.hpp"
#include <fstream>
#include <boost/asio.hpp>

void c_url_downloader::download_file (const std::string &file_address, const std::string &out_path)
{
	using namespace boost::asio;
	io_service io_servise;
	ip::tcp::resolver resolver(io_servise);
	ip::tcp::resolver::query query(file_address, "http");
	ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	ip::tcp::resolver::iterator end;

	std::ofstream out_file(out_path);
}
