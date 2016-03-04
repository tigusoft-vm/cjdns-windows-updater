#ifndef I_DOWNLOADER_H
#define I_DOWNLOADER_H

#include <ostream>
#include <string>

class i_downloader
{
	public:
		/**
		 * Download file from file_address and write to out_stream
		 * @param file_address remote file address
		 * @param out_stream out ref, must by ready for call write()
		 */
		virtual void download_file(const std::string &file_address, std::ostream &out_stream) = 0;
		virtual ~i_downloader() = default;
};

#endif // I_DOWNLOADER_H