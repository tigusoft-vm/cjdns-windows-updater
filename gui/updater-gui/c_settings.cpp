#include "c_settings.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

c_settings::c_settings()
{
}

c_settings &c_settings::getInstance() {
    static c_settings instance;
    return instance;
}

void c_settings::load_settings(const std::string &file_path) {
    using namespace boost::property_tree;
    ptree tree;
    read_xml(file_path, tree);
    tree.get("settings.lang", language);
    tree.get("settings.autorun", autorun);
}

void c_settings::save_settings(const std::string &file_path) {
    using namespace boost::property_tree;
    ptree tree;
    tree.put("settings.lang", language);
    tree.put("settings.autorun", autorun);
    write_xml(file_path, tree);
}
