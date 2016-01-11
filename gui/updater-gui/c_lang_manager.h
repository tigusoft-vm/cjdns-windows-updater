#ifndef C_LANG_MANAGER_H
#define C_LANG_MANAGER_H

#include <memory>
#include <QApplication>
#include <qtranslator.h>

class c_lang_manager
{
    public:
        c_lang_manager(const std::shared_ptr<QApplication> &qapp);
        std::string get_current_language() const; ///< return current language(short name) e.g. EN
        void set_current_language(const std::string &language); ///< @param language: short name of language e.g. EN
        const std::map<std::string, std::string>& get_lang_map() const;
    private:
        std::weak_ptr<QApplication> m_qapplication;
        std::string m_current_language; ///< short name e.g. EN
        std::map<std::string, std::string> m_lang_files_map; ///< short name to display => lang file path e.g. EN => language/EN.qm
        QTranslator m_qtranslator;
};

#endif // C_LANG_MANAGER_H
