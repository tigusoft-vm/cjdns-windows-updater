#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "c_updater.hpp"
#include "settings_window.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<c_updater> updater_ptr, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    std::weak_ptr<c_updater> m_updater;
    std::unique_ptr<Settings_window> m_setting_window;
};

#endif // MAINWINDOW_H
