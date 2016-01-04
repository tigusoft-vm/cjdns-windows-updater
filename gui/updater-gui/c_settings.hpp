#ifndef C_SETTINGS_HPP
#define C_SETTINGS_HPP

// singleton
class c_settings
{
    private:
        c_settings();
    public:
        c_settings(const c_settings &) = delete;
        void operator= (const c_settings &) = delete;

        static c_settings& getInstance();
    private:
        void load_settings();
};

#endif // C_SETTINGS_HPP
