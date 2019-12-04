cmake_minimum_required(VERSION 3.14.4)
project(Player2 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Player2 SHARED
    Player2.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Player2 PROPERTIES PUBLIC_HEADER Player2.hpp)
target_include_directories(Player2 PRIVATE .)