#include "mainwindow.h"
#include "c_updater.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    c_updater updater;
    return a.exec();
}
