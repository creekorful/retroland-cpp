cmake_minimum_required(VERSION 3.17)
project(Retroland)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Retroland_Editor src/Editor/main.cpp
        src/TileMap/TileMap.cpp src/TileMap/TileMap.h
        src/Editor/Inventory.cpp src/Editor/Inventory.h)

target_link_libraries(Retroland_Editor sfml-graphics sfml-window sfml-system)