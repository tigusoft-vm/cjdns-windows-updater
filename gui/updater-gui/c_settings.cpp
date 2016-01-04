#include "c_settings.hpp"

c_settings::c_settings()
{
}

c_settings &c_settings::getInstance() {
    static c_settings instance;
    return instance;
}
