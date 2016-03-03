#ifndef C_WINDOWS_UTILITY_HPP
#define C_WINDOWS_UTILITY_HPP

#if defined _WIN32 || defined __CYGWIN__

namespace win_utility {

class c_windows_utility {
	public:
		/**
		 * Routine Description: This routine returns TRUE if the caller's
		 * process is a member of the Administrators local group. Caller is NOT
		 * expected to be impersonating anyone and is expected to be able to
		 * open its own process and process token.
		 * Arguments: None.
		 * Return Value:
		 * TRUE - Caller has Administrators local group.
		 * FALSE - Caller does not have Administrators local group.
		 * 
		 * @throw std::runtime_error
		 * Exception safety: strong exception guarantee
		 * 
		 */
		static bool is_user_admin();
};
	
} // namespace

#endif // define windows

#endif