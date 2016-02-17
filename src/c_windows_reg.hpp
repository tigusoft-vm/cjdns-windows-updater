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
			 * @throw std::runtime_error if error
			 */
			static std::string get_register_value(HKEY root, const std::string &key, const std::string &name);
			
			
			static void set_register_value();
	};
	
} // namespace

#endif // define windows

#endif