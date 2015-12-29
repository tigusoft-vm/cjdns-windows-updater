cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

file(GLOB gui_sources "*.cpp")
add_executable(gui ${gui_sources} ${source_files})
target_link_libraries(gui updater boost_system pthread)
qt5_use_modules(gui Widgets)