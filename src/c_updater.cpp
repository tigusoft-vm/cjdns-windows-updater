#include "c_updater.hpp"
#include "c_http_downloader.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#ifdef __CYGWIN__
#include <sstream>
namespace std {
unsigned int stol(const std::string &str) {
    std::stringstream stream;
	stream.str(str);
	unsigned int ret;
	stream >> ret;
	return ret;
}
} // namespace std
#endif

c_updater::c_updater() :
	m_downloader(new c_http_downloader)
{
}

unsigned int c_updater::get_remote_version() {
	std::ostringstream oss;
	m_downloader->download_file(m_server_address + "/ver", oss);
	return get_version_number(std::move(oss.str()));
}

bool c_updater::check_new_version() {
    return get_remote_version() > get_local_version();
}

unsigned int c_updater::get_version_number(std::string &&version_str) {
	auto it = version_str.begin();
	while (it < version_str.end()) {
		if (!std::isdigit(*it)) {
			version_str.erase(it);
			continue;
		}
		it++;
	}
	unsigned int version_number = std::stol(version_str);
	return version_number;
}