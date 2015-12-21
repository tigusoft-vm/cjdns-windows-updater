#include "c_updater.hpp"
#include "c_http_downloader.hpp"

c_updater::c_updater() :
	m_downloader(new c_http_downloader)
{
}

