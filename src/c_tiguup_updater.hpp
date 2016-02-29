#ifndef C_TIGUUP_UPDATER
#define C_TIGUUP_UPDATER

#include "c_updater.hpp"

class c_tiguup_updater final : public c_updater {
	public:
		c_tiguup_updater(const std::string &server_address, std::unique_ptr<i_downloader> &&downloader);
		virtual void update() override;
	private:
		unsigned int get_local_version() override;
		unsigned int get_remote_version() override;
		std::string get_install_path();
};

#endif