#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include <QDialog>
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

protected:
    void changeEvent(QEvent *event);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Settings_window *ui;
    void showEvent(QShowEvent *event) override;
};

#endif // SETTINGS_WINDOW_HPP
