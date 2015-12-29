cmake_minimum_required(VERSION 2.8.11)
project(cjdns-windows-updater)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror -pedantic")

file(GLOB source_sha "sha_src/*.cpp")
include_directories(src)

add_subdirectory(gui/updater-gui)
add_subdirectory(src)

add_executable(cjdns-windows-updater main.cpp ${source_sha})
target_link_libraries(cjdns-windows-updater updater boost_system pthread)
