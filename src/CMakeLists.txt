cmake_minimum_required(VERSION 2.8.11)

file(GLOB updater_sources "*.cpp")
add_library(updater ${updater_sources})
target_link_libraries(updater boost_system boost_filesystem pthread)