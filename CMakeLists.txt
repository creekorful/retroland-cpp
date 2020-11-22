cmake_minimum_required(VERSION 3.17)
project(retroland)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(retroland src/main.cpp)

target_link_libraries(retroland sfml-graphics sfml-window sfml-system)