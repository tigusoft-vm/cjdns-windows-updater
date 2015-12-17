#ifndef I_DOWNLOADER_H
#define I_DOWNLOADER_H

#include <string>

class i_downloader
{
	public:
		/**
		 * Download file from @param file_address and save as @param out_path
		 */
		virtual void download_file(const std::string &file_address, const std::string &out_path) = 0;
		virtual ~i_downloader() = default;
};

#endif // I_DOWNLOADER_H

