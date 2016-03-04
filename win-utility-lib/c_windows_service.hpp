#ifndef C_WINDOWS_SERVEICE_HPP
#define C_WINDOWS_SERVEICE_HPP

#if defined _WIN32 || defined __CYGWIN__

#include <string>

namespace win_utility {

class c_windows_service {
	public:
		/**
		 * start service @param service_name
		 * @throw std::runtime_error if error
		 * This function requires administrator permissions. Else throw std::runtime_error
		 * \par Exception safety
		 * strong exception guarantee
		 */
		static void stop_service(const std::string &service_name);

		/**
		 * stop service @param service_name
		 * @throw std::runtime_error if error
		 * This function requires administrator permissions. Else throw std::runtime_error
		 * Exception safety: strong exception guarantee
		 */
		static void start_service(const std::string &service_name);
};

} // namespace

#endif // define windows

#endif