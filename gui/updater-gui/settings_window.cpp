#include "settings_window.hpp"
#include "c_settings.hpp"
#include "ui_settings_window.h"

#include <boost/filesystem.hpp>
#include <iostream>

#define SETTINGS_FILE "settings.xml"
#define LANG_DIR_NAME "language"

Settings_window::Settings_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings_window)
{
    namespace fs = boost::filesystem;
    ui->setupUi(this);
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
                std::cout << "lang_file_path " << lang_file_path << std::endl;
                std::cout << "extension " << extension << std::endl;
                if (extension != ".qm") continue;

                QString short_name = QString::fromStdString(lang_file_path);
                ui->langComboBox->addItem(QString::fromStdString(lang_file_path));
            }
        }
    }
}

Settings_window::~Settings_window()
{
    delete ui;
}

void Settings_window::on_buttonBox_accepted()
{
    c_settings::getInstance().autorun = ui->autorunCheckBox->isChecked();
    c_settings::getInstance().language = ui->langComboBox->currentText().toStdString();
    c_settings::getInstance().save_settings(SETTINGS_FILE);
}

void Settings_window::showEvent(QShowEvent *event) {
    Q_UNUSED(event);
    c_settings::getInstance().load_settings(SETTINGS_FILE);
}
