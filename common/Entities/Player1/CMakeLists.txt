cmake_minimum_required(VERSION 3.14.4)
project(Player1 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Player1 SHARED
    Player1.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Player1 PROPERTIES PUBLIC_HEADER Player1.hpp)
target_include_directories(Player1 PRIVATE .)