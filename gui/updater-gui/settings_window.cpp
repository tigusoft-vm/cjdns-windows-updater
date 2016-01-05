#include "settings_window.hpp"
#include "c_settings.hpp"
#include "ui_settings_window.h"

Settings_window::Settings_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings_window)
{
    ui->setupUi(this);
}

Settings_window::~Settings_window()
{
    delete ui;
}

void Settings_window::on_buttonBox_accepted()
{
    c_settings::getInstance().autorun = ui->autorunCheckBox->isChecked();
    c_settings::getInstance().language = ui->langComboBox->currentText().toStdString();
    c_settings::getInstance().save_settings("test_settings.xml"); // TODO file name
}
