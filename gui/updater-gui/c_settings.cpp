#include "c_settings.hpp"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <QString>

#define LANG_DIR_NAME "language"

c_settings::c_settings() :
    current_language("EN"),
    autorun(true)
{
    load_languages();
}

void c_settings::load_languages() {
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
                lang_files_map.emplace(short_name, lang_file_path);
            }
        }
    }
}

c_settings &c_settings::getInstance() {
    static c_settings instance;
    return instance;
}

void c_settings::load_settings(const std::string &file_path) {
    if (!boost::filesystem::exists(file_path)) {
        return;
    }
    using namespace boost::property_tree;
    ptree tree;
    read_xml(file_path, tree);
    tree.get("settings.lang", current_language);
    tree.get("settings.autorun", autorun);
}

void c_settings::save_settings(const std::string &file_path) {
    using namespace boost::property_tree;
    ptree tree;
    tree.put("settings.lang", current_language);
    tree.put("settings.autorun", autorun);
    write_xml(file_path, tree);
}
