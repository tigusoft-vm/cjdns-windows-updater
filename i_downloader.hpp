#ifndef I_DOWNLOADER_H
#define I_DOWNLOADER_H

#include <string>

class i_downloader
{
	public:
		virtual void download_file(const std::string &file_address, const std::string &out_path) = 0;
		virtual ~c_downloader_iface();
};

#endif // C_DOWNLOADER_H

