#ifndef C_TIGUUP_UPDATER
#define C_TIGUUP_UPDATER

#include "c_updater.hpp"

class c_tiguup_updater : public c_updater {
	public:
		virtual void update() override;
};

#endif