cmake_minimum_required(VERSION 2.8.11)

#find_package(Qt4 REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

#include(${QT_USE_FILE})
#add_definitions(${QT_DEFINITIONS})

file(GLOB gui_sources "*.cpp")
#file(GLOB gui_heareds "*.h")
#file(GLOB gui_forms "*.ui")

#include_directories("updater-gui")
add_executable(gui ${gui_sources})
qt5_use_modules(gui Widgets)