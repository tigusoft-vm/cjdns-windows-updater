#ifndef C_UPDATER_H
#define C_UPDATER_H

#include <memory>
#include <string>

#include "i_downloader.hpp"

class c_updater {
	public:
		c_updater(const std::string &server_address, std::unique_ptr<i_downloader> &&downloader);
		virtual void update() = 0;
		virtual ~c_updater() = default;
	protected:
		std::unique_ptr<i_downloader> m_downloader;
		virtual unsigned int get_remote_version() = 0; ///< @returns version on server (server_address/ver)
		virtual unsigned int get_local_version() = 0; ///< @returns local version
		/**
		 * Remove non digit chars from @param version_str
		 * for @param version_str == 17.1-4-test returns 1714
		 */
		virtual unsigned int get_version_number(std::string &&version_str);
		const std::string m_server_address;
};

#endif // C_UPDATER_H
