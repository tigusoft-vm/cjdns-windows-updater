#include "mainwindow.h"
#include "settings_window.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<c_updater> updater_ptr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_updater(updater_ptr),
    m_setting_window(new Settings_window)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settingsButton_clicked()
{
    m_setting_window->show();
}
