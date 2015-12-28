cmake_minimum_required(VERSION 2.8)
project(cjdns-windows-updater)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror -pedantic")

file(GLOB source_files "src/*.cpp")
file(GLOB source_sha "sha_src/*.cpp")
include_directories(src)

add_executable(cjdns-windows-updater main.cpp ${source_files} ${source_sha})
target_link_libraries(cjdns-windows-updater boost_system pthread)
