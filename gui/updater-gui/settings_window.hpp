#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include <QDialog>
#include <map>
#include <string>

namespace Ui {
class Settings_window;
}

class Settings_window : public QDialog
{
    Q_OBJECT

public:
    explicit Settings_window(QWidget *parent = 0);
    ~Settings_window();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Settings_window *ui;
    void showEvent(QShowEvent *event) override;
    // short name dispalyed on combobox => lang file path
    std::map<QString, std::string> m_lang_files_map;
};

#endif // SETTINGS_WINDOW_HPP
