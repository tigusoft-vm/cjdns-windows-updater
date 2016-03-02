#ifndef C_TIGUUP_UPDATER
#define C_TIGUUP_UPDATER

#include "c_updater.hpp"

class c_tiguup_updater final : public c_updater {
	public:
		c_tiguup_updater(const std::string &server_address, std::unique_ptr<i_downloader> &&downloader);
		/**
		 * Check remote and local version. If remote > local update
		 * Else return.
		 */
		virtual void update() override;

		/**
		 * @return true if update in progress
		 * If returns true tigu-up.exe is lunched and wait for end of this process
		 * Exception safety: No-throw guarantee
		 */
		bool update_in_progress() noexcept;
	private:
		unsigned int get_local_version() override;
		unsigned int get_remote_version() override;
		std::string get_install_path();
		bool m_update_in_progress; ///< set true if update in progress
};

#endif