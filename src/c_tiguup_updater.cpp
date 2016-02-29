#include "c_tiguup_updater.hpp"
#include "../win-utility-lib/c_windows_reg.hpp"

#include <iostream> // XXX
#include <sstream>

#ifdef __CYGWIN__
#include <sstream>
namespace std {
template <typename T>
std::string to_string(T val) {
    std::stringstream stream;
    stream << val;
    return stream.str();
}
} // namespace std
#endif


c_tiguup_updater::c_tiguup_updater(const std::string &server_address, std::unique_ptr<i_downloader> &&downloader) :
	c_updater(server_address, std::move(downloader))
{
}

void c_tiguup_updater::update() {
	unsigned int local_version = get_local_version();
	unsigned int remote_version = get_remote_version();
	std::cout << "updater local version: " << local_version << std::endl;
	std::cout << "updater remote version: " << remote_version << std::endl;
	std::cout << "install path: " << get_install_path() << std::endl;

	if (local_version >= remote_version) {
		std::cout << "update exit" << std::endl;
		return;
	}

	std::cout << "download remote version" << std::endl;

	std::string PID = std::to_string(GetCurrentProcessId());
	std::cout << "my pid " << PID << std::endl;
	std::unique_ptr<char[]> pid_arr(new char[PID.size() + 1]);
	PID.copy(pid_arr.get(), PID.size());
	pid_arr[PID.size()] = '\0';

	std::cout << "run tigu-up.exe" << std::endl;
	STARTUPINFO info;
	PROCESS_INFORMATION processInfo;
	CreateProcess("tigu-up.exe", pid_arr.get(), nullptr, nullptr, true, 0, nullptr, nullptr, &info, &processInfo);
	std::terminate(); // TODO
}

// updater version saved in HKEY_LOCAL_MACHINE\SOFTWARE\cjdns in updater-ver
unsigned int c_tiguup_updater::get_local_version() {
	std::string ver(
		win_utility::c_windows_reg::get_register_value(HKEY_LOCAL_MACHINE, R"(SOFTWARE\cjdns)", "updater-ver") 
	);
	unsigned int ret_ver = *reinterpret_cast<const DWORD*>(ver.data());
	return ret_ver;
}

unsigned int c_tiguup_updater::get_remote_version() {
	std::ostringstream oss;
	m_downloader->download_file(m_server_address + "/updater/ver", oss);
	return get_version_number(std::move(oss.str()));
}

std::string c_tiguup_updater::get_install_path() {
	std::string path = win_utility::c_windows_reg::get_register_value(HKEY_LOCAL_MACHINE, R"(SYSTEM\ControlSet001\services\cjdns)", "ImagePath");
	size_t pos = path.find_last_of('\\');
	path.erase(pos);
	return path;
}