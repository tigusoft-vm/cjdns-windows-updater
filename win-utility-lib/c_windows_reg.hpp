#ifndef C_WINDOWS_REG_HPP
#define C_WINDOWS_REG_HPP

#if defined _WIN32 || defined __CYGWIN__
#include <string>
#include <windows.h>
#include <winreg.h>

namespace win_utility {
	class c_windows_reg {
		public:
			/**
			 * @param root 
			 * use one of predefined keys:
			 * HKEY_CLASSES_ROOT
			 * HKEY_CURRENT_CONFIG
			 * HKEY_CURRENT_USER
			 * HKEY_LOCAL_MACHINE
			 * HKEY_USERS
			 *
			 * @param key 
			 * path of register key without root name
			 *
			 * @param name
			 * name of the registry subkey to be opened
			 *
			 * @returns register value as binary data
			 *
			 * @throw std::runtime_error if error
			 * \par Exception safety
			 * strong exception guarantee
			 */
			static std::string get_register_value(HKEY root, const std::string &key, const std::string &name);
			
			/**
			 * @param root 
			 * use one of predefined keys:
			 * HKEY_CLASSES_ROOT
			 * HKEY_CURRENT_CONFIG
			 * HKEY_CURRENT_USER
			 * HKEY_LOCAL_MACHINE
			 * HKEY_USERS
			 * 
			 * @param key 
			 * path of register key without root name
			 *
			 * @param name
			 * name of the registry subkey to be opened
			 * 
			 * @param type
			 * type of register value
			 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms724884
			 * 
			 * @param data
			 * the data to be stored
			 * For string-based types, such as REG_SZ, the string must be null-terminated. With
			 * the REG_MULTI_SZ data type, the string must be terminated with two null characters.
			 * String-literal values must be formatted using a backslash preceded by another backslash
			 * as an escape character. For example, specify "C:\\mydir\\myfile" to store the string
			 * "C:\mydir\myfile".
			 * 
			 * @param size_of_data
			 * The size of the information pointed to by the lpData parameter, in bytes. If the data is
			 * of type REG_SZ, REG_EXPAND_SZ, or REG_MULTI_SZ, cbData must include the size of the
			 * terminating null character or characters.
			 *
			 * @throw std::runtime_error if error
			 * Exception safety: strong exception guarantee
			 * 
			 * This function requires administrator permissions. Else throw std::runtime_error
			 */
			static void set_register_value(HKEY root, const std::string &key, const std::string &name, DWORD type, const BYTE *data, DWORD size_of_data);
	};
	
} // namespace

#endif // define windows

#endif