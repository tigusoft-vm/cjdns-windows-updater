#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<c_updater> updater_ptr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_updater(updater_ptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
