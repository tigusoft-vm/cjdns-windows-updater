#ifndef C_UPDATER_H
#define C_UPDATER_H

#include <memory>
#include <string>

#include "i_downloader.hpp"

class c_updater
{
	public:
		c_updater();
		virtual void update();
        virtual bool check_new_version(); ///< @return true if local version < server version
		virtual ~c_updater() = default;
	protected:
		std::unique_ptr<i_downloader> m_downloader;
		virtual unsigned int get_remote_version(); ///< @returns version on server
		virtual unsigned int get_local_version(); ///< @returns local version
		/**
		 * Remove non digit chars from @param version_str
		 * for @param version_str == 17.1-4-test returns 1714
		 */
		virtual unsigned int get_version_number(std::string &&version_str);
};

#endif // C_UPDATER_H
