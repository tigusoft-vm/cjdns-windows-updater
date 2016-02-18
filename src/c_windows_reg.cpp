#if defined _WIN32 || defined __CYGWIN__

#include "c_windows_reg.hpp"
#include "c_windows_utility.hpp"
#include <stdexcept>

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

void c_windows_reg::set_register_value(HKEY root, const std::string &key, const std::string &name, DWORD type, const BYTE *data, DWORD size_of_data) {
	if (!c_windows_utility::is_user_admin())
		throw std::runtime_error("required administrator permissions");
	HKEY hKey;
	DWORD dwFunc;
	LONG  ret;

	ret = RegCreateKeyEx(root, key.c_str(), 0, nullptr, 0, KEY_WRITE, NULL, &hKey, &dwFunc);
	if(ret != ERROR_SUCCESS)
		throw std::runtime_error("RegCreateKeyEx returns " + std::to_string(ret));

	// set register value
	ret = RegSetValueEx(hKey, name.c_str(), 0, type, data, size_of_data);
	if(ret != ERROR_SUCCESS)
		throw std::runtime_error("RegSetValueEx returns " + std::to_string(ret));
}

} // namespace

#endif