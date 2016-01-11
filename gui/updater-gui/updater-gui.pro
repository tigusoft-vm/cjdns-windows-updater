#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T14:52:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

TARGET = updater-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/c_http_downloader.cpp \
    ../../src/c_updater.cpp \
    settings_window.cpp \
    c_settings.cpp \
    c_lang_manager.cpp

HEADERS  += mainwindow.h \
    settings_window.hpp \
    c_settings.hpp \
    c_lang_manager.h
INCLUDEPATH += ../../src/

LIBS += -lboost_system \
    -lboost_filesystem

FORMS    += mainwindow.ui \
    settings_window.ui

TRANSLATIONS = language/EN.ts \
            language/PL.ts
