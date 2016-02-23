#ifndef C_CJDNS_UPDATER_HPP
#define C_CJDNS_UPDATER_HPP

#include "c_updater.hpp"
#include <string>
#include <windows.h>
#include <winreg.h>
#include <winsvc.h>

class c_cjdns_updater : public c_updater {
	public:
		void update() override;
	private:
		std::string get_cjdns_install_path(); ///< reutrn cjdns install path i.e. "C:\Program Files (x86)\cjdns"
		unsigned int get_local_version() override;
		const std::string m_service_name = "cjdns";
};

#endif