#include "c_tiguup_updater.hpp"
#include "../win-utility-lib/c_windows_reg.hpp"

#include <fstream>
#include <sstream>

#include <chrono> // XXX
#include <iostream> // XXX
#include <thread> // XXX

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
	c_updater(server_address, std::move(downloader)),
	m_update_in_progress(false)
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
	const std::string new_updater_wrapper("updater_new.exe");
	std::ofstream downloaded_file(new_updater_wrapper);
	m_downloader->download_file(m_server_address + "/updater/updater.exe", downloaded_file);
	downloaded_file.close();

	std::string PID = std::to_string(GetCurrentProcessId());
	std::cout << "my pid " << PID << std::endl;
	std::unique_ptr<char[]> pid_arr(new char[PID.size() + 1]);
	int cpy_chars = PID.copy(pid_arr.get(), PID.size());
	std::cout << "cpy_chars " << cpy_chars << std::endl;
	pid_arr[PID.size()] = '\0';
	std::cout << "pid array " << pid_arr.get() << std::endl;

	std::cout << "run " << new_updater_wrapper << std::endl;
	STARTUPINFO info;
	memset(&info, 0, sizeof(info)); // mingw warnings "missing initializer for member"
	info.cb = sizeof(info);
	PROCESS_INFORMATION processInfo;
	int ret = CreateProcess("tigu-up.exe", pid_arr.get(), nullptr, nullptr, true, 0, nullptr, nullptr, &info, &processInfo);
	std::cout << "ret " << ret << std::endl;
	std::cout << "last error: " << GetLastError() << std::endl;
	m_update_in_progress = true;
}

bool c_tiguup_updater::update_in_progress() {
	return m_update_in_progress;
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