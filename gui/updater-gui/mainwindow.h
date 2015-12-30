#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "c_updater.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<c_updater> updater_ptr, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::weak_ptr<c_updater> m_updater;
};

#endif // MAINWINDOW_H
