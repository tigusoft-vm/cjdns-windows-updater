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
		void stop_cjdns_service();
		void start_cjdns_service();
		std::string get_register_value(HKEY root, const std::string &key, const std::string &name);
		const std::string m_service_name = "cjdns";
};

#endif