#ifndef I_DOWNLOADER_H
#define I_DOWNLOADER_H

#include <ostream>
#include <string>

class i_downloader
{
	public:
		/**
		 * Download file from @param file_address and write to @param out_stream
		 * @param out_stream out ref, must by ready for call write()
		 * out_stream is empty if internal error
		 */
		virtual void download_file(const std::string &file_address, std::ostream &out_stream) = 0;
		virtual ~i_downloader() = default;
};

#endif // I_DOWNLOADER_H

