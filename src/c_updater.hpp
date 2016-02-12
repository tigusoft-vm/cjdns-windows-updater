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
        bool check_new_version(); ///< @return true if local version < server version
		virtual ~c_updater() = default;
	protected:
		std::unique_ptr<i_downloader> m_downloader;
		unsigned int get_remote_version(); ///< @returns version on server
		unsigned int get_local_version(); ///< @returns local version
};

#endif // C_UPDATER_H
