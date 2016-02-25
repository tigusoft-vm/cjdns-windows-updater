#ifndef C_WINDOWS_UTILITY_HPP
#define C_WINDOWS_UTILITY_HPP

#if defined _WIN32 || defined __CYGWIN__

namespace win_utility {

class c_windows_utility {
	public:
		static bool is_user_admin();
};
	
} // namespace

#endif // define windows

#endif