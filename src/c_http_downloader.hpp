#ifndef C_HTTP_DOWNLOADER_H
#define C_HTTP_DOWNLOADER_H

#include "i_downloader.hpp"

class c_http_downloader final :  public i_downloader
{
	public:
		/**
		 * @param file_address remote file address, e.g 127.0.0.1/file.txt
		 * @param out_stream out ref, must by ready for call write()
		 * 
		 * @throw boost::system::system_error if asio error
		 * @throw std::invalid_argument if invalid @param file_address
		 * Exception safety: basic exception guarantee (data in out_stream)
		 */
		virtual void download_file(const std::string &file_address, std::ostream &out_stream) override;
	private:
		std::string generate_request(const std::string& hostname, const std::string& path);
};

#endif // C_HTTP_DOWNLOADER_H
