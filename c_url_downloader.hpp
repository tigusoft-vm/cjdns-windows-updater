#ifndef C_URL_DOWNLOADER_H
#define C_URL_DOWNLOADER_H

#include "i_downloader.hpp"

class c_url_downloader :  i_downloader
{
	public:
		virtual void download_file(const std::string &file_address, const std::string &out_path) override;
	private:
		std::string generate_request(const std::string& hostname, const std::string& path);
};

#endif // C_URL_DOWNLOADER_H
