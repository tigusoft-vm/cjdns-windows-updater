#ifndef C_UPDATER_H
#define C_UPDATER_H

#include <memory>
#include <string>

#include "i_downloader.hpp"

class c_updater
{
	public:
		c_updater();
		void update();
	private:
		std::unique_ptr<i_downloader> m_downloader;
};

#endif // C_UPDATER_H
