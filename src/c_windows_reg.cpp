#if defined _WIN32 || defined __CYGWIN__

#include "c_windows_reg.hpp"
#include <stdexcept>

namespace win_utility {

std::string c_windows_reg::get_register_value(HKEY root, const std::string &key, const std::string &name) {
	HKEY hKey;
	if (RegOpenKeyEx(root, key.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
		throw std::runtime_error("could not open registry key");
	}
	DWORD type = 0;
	DWORD cbData = 0;
	if (RegQueryValueEx(hKey, name.c_str(), nullptr, &type, nullptr, &cbData) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		throw std::runtime_error("Could not read registry value");
	}

	std::string value(cbData, '\0');
	if (RegQueryValueEx(hKey, name.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(&value[0]), &cbData) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		throw std::runtime_error("Could not read registry value");
	}

	RegCloseKey(hKey);
	return value;
}

} // namespace

#endif