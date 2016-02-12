cmake_minimum_required(VERSION 2.8.11)
project(cjdns-windows-updater)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

include_directories(src)

#add_subdirectory(gui/updater-gui)
add_subdirectory(src)

add_executable(cjdns-windows-updater main.cpp)
target_link_libraries(cjdns-windows-updater updater boost_system pthread)
