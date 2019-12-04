cmake_minimum_required(VERSION 3.14.4)
project(Player4 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Player4 SHARED
    Player4.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Player4 PROPERTIES PUBLIC_HEADER Player4.hpp)
target_include_directories(Player4 PRIVATE .)