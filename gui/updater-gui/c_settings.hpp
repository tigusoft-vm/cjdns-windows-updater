#ifndef C_SETTINGS_HPP
#define C_SETTINGS_HPP

#include <map>
#include <string>

// singleton
class c_settings
{
    private:
        c_settings();
        void load_languages();

    public:
        c_settings(const c_settings &) = delete;
        void operator= (const c_settings &) = delete;

        static c_settings& getInstance();

        std::string current_language; ///< short name e.g. EN
        std::map<std::string, std::string> m_lang_files_map; ///< short name to display => lang file path

        bool autorun;

        void load_settings(const std::string &file_path);
        void save_settings(const std::string &file_path);
};

#endif // C_SETTINGS_HPP
