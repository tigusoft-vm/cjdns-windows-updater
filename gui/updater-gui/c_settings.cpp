#include "c_settings.hpp"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <QString>

c_settings::c_settings() :
    //current_language("EN"),
    autorun(true)
{
    load_languages();
}

void c_settings::load_languages() {

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
    // TODO tree.get("settings.lang", current_language);
    tree.get("settings.autorun", autorun);
}

void c_settings::save_settings(const std::string &file_path) {
    using namespace boost::property_tree;
    ptree tree;
    // TODO tree.put("settings.lang", current_language);
    tree.put("settings.autorun", autorun);
    write_xml(file_path, tree);
}
