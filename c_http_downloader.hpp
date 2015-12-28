#ifndef C_HTTP_DOWNLOADER_H
#define C_HTTP_DOWNLOADER_H

#include "i_downloader.hpp"

class c_http_downloader :  public i_downloader
{
	public:
		/**
		 * @param file_address remote file address, e.g 127.0.0.1/file.txt
		 */
		virtual void download_file(const std::string &file_address, std::ostream &out_stream) override;
	private:
		std::string generate_request(const std::string& hostname, const std::string& path);
};

#endif // C_HTTP_DOWNLOADER_H
