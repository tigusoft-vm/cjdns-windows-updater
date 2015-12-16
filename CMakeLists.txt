project(cjdns-windows-updater)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror -pedantic")

file(GLOB source_files "*.cpp")

add_executable(cjdns-windows-updater ${source_files})
target_link_libraries(cjdns-windows-updater boost_system)