#ifndef C_UPDATER_H
#define C_UPDATER_H

#include <memory>
#include <string>

#include "i_downloader.hpp"

class c_updater
{
	public:
		c_updater();
		virtual void update() = 0;
		virtual ~c_updater() = default;
	protected:
		std::unique_ptr<i_downloader> m_downloader;
		virtual unsigned int get_remote_version(); ///< @returns version on server (server_address/ver)
		virtual unsigned int get_local_version() = 0; ///< @returns local version
		/**
		 * Remove non digit chars from @param version_str
		 * for @param version_str == 17.1-4-test returns 1714
		 */
		virtual unsigned int get_version_number(std::string &&version_str);
		const std::string m_server_address = "fc72:aa65:c5c2:4a2d:54e:7947:b671:e00c";
};

#endif // C_UPDATER_H
