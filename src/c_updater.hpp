#ifndef C_UPDATER_H
#define C_UPDATER_H

#include <memory>
#include <string>

#include "i_downloader.hpp"

class c_updater {
	public:
		c_updater(const std::string &server_address, std::unique_ptr<i_downloader> &&downloader);
		/**
		 * Check local and remote(server) version. If remote version > local version then update
		 * else return;
		 */
		virtual void update() = 0;
		virtual ~c_updater() = default;
	protected:
		std::unique_ptr<i_downloader> m_downloader;
		virtual unsigned int get_remote_version() = 0; ///< @returns version on server
		virtual unsigned int get_local_version() = 0; ///< @returns local version

		/**
		 * Remove non digit chars from version_str
		 * i.e. for version_str == 17.1-4-test returns 1714
		 * @param version_str version as string
		 * @throw std::invalid_argument if no digits in @param version_str
		 * \par Exception safety
		 * strong exception guarantee
		 */
		virtual unsigned int get_version_number(std::string &&version_str);
		const std::string m_server_address;
};

#endif // C_UPDATER_H
