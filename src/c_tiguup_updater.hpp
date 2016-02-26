#ifndef C_TIGUUP_UPDATER
#define C_TIGUUP_UPDATER

#include "c_updater.hpp"

class c_tiguup_updater final : public c_updater {
	public:
		c_tiguup_updater();
		virtual void update() override;
	private:
		 unsigned int get_local_version() override;
};

#endif