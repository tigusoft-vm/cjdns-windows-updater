#include "settings_window.hpp"
#include "c_settings.hpp"
#include "ui_settings_window.h"

Settings_window::Settings_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings_window)
{
    ui->setupUi(this);
    for (const auto &lang : c_settings::getInstance().lang_manager->get_lang_map()) {
        ui->langComboBox->addItem(QString::fromStdString(lang.first));
    }
    ui->langComboBox->setCurrentText(QString::fromStdString(c_settings::getInstance().lang_manager->get_current_language()));
    ui->autorunCheckBox->setChecked(c_settings::getInstance().autorun);
}

Settings_window::~Settings_window()
{
    delete ui;
}

void Settings_window::changeEvent(QEvent *event) {
    if (event == nullptr) return;
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void Settings_window::on_buttonBox_accepted() {
    c_settings::getInstance().autorun = ui->autorunCheckBox->isChecked();
    c_settings::getInstance().lang_manager->set_current_language(ui->langComboBox->currentText().toStdString());
    c_settings::getInstance().save_settings();
}

void Settings_window::showEvent(QShowEvent *event) {
    Q_UNUSED(event);
    c_settings::getInstance().load_settings();
}
