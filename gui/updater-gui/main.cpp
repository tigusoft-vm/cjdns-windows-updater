#include "mainwindow.h"
#include "c_updater.hpp"
#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{
    std::shared_ptr<c_updater> updater_ptr = std::make_shared<c_updater>();
    std::shared_ptr<QApplication> a = std::make_shared<QApplication>(argc, argv);
    MainWindow w(updater_ptr);
    w.show();
    return a->exec();
}
