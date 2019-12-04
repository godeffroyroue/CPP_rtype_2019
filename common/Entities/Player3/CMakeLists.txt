cmake_minimum_required(VERSION 3.14.4)
project(Player3 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Player3 SHARED
    Player3.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Player3 PROPERTIES PUBLIC_HEADER Player3.hpp)
target_include_directories(Player3 PRIVATE .)