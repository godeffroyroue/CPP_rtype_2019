cmake_minimum_required(VERSION 3.14.4)
project(Shoot1 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Shoot1 SHARED
    Shoot1.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Shoot1 PROPERTIES PUBLIC_HEADER Shoot1.hpp)
target_include_directories(Shoot1 PRIVATE .)