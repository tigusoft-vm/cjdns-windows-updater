#include "c_lang_manager.h"
#include <boost/filesystem.hpp>

#define LANG_DIR_NAME "language"

c_lang_manager::c_lang_manager(const std::shared_ptr<QApplication> &qapp) :
    m_qapplication(qapp),
    m_current_language("EN")
{
    namespace fs = boost::filesystem;
    fs::path lang_dir(LANG_DIR_NAME);
    fs::directory_iterator end_iter;
    if (fs::exists(lang_dir) && fs::is_directory(lang_dir)) {
        // for each file in directory
        for (fs::directory_iterator dir_it(lang_dir); dir_it != end_iter; ++dir_it) {
            if (fs::is_regular_file(dir_it->status())) {
                std::string lang_file_path(dir_it->path().generic_string());
                if (lang_file_path.size() < 3) continue;
                // check last 3 chars
                std::string extension(lang_file_path.substr(lang_file_path.size() - 3));
                if (extension != ".qm") continue;

                // lang_file_path == e.g. language/EN.qm
                // generate short name for combobox
                std::string short_name = lang_file_path;
                short_name.erase(0, std::strlen(LANG_DIR_NAME) + 1); // remove LANG_DIR_NAME + '/' char
                short_name.erase(short_name.size() - 3, 3); // remove last 3 chars (.qm)
                m_lang_files_map.emplace(short_name, lang_file_path);
            }
        }
    }
}

std::string c_lang_manager::get_current_language() const {
    return m_current_language;
}

void c_lang_manager::set_current_language(const std::string &language) { // TODO
    if (language == m_current_language) return;

}

const std::map<std::string, std::string>& c_lang_manager::get_lang_map() const {
    return m_lang_files_map;
}
