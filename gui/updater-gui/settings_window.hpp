#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include <QDialog>

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
};

#endif // SETTINGS_WINDOW_HPP
