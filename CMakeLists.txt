cmake_minimum_required(VERSION 2.8.11)
project(cjdns-windows-updater)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

include_directories(src)

#add_subdirectory(gui/updater-gui)
add_subdirectory(src)
add_subdirectory(win-utility-lib)

add_executable(tigu-up tigu_up_main.cpp)
target_link_libraries(tigu-up boost_system boost_filesystem)

add_executable(cjdns-windows-updater main.cpp)
target_link_libraries(cjdns-windows-updater updater win-utility-lib boost_system pthread)
