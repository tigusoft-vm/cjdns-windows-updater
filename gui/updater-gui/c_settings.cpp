#include "c_settings.hpp"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <QString>

c_settings::c_settings() :
    autorun(true)
{
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
    std::string current_language;

    current_language = tree.get<std::string>("settings.lang");
    lang_manager->set_current_language(current_language);

    autorun = tree.get("settings.autorun", true);

    std::cout << "*****" << std::endl;
    std::cout << "c_settings::load_settings" << " current_language " << current_language << std::endl;
    std::cout << "c_settings::load_settings" << " autorun " << autorun << std::endl;
}

void c_settings::save_settings(const std::string &file_path) {
    using namespace boost::property_tree;
    ptree tree;
    tree.put("settings.lang", lang_manager->get_current_language());
    tree.put("settings.autorun", autorun);
    write_xml(file_path, tree);
}
