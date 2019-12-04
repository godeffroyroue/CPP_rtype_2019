cmake_minimum_required(VERSION 3.14.4)
project(Shoot3 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Shoot3 SHARED
    Shoot3.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Shoot3 PROPERTIES PUBLIC_HEADER Shoot3.hpp)
target_include_directories(Shoot3 PRIVATE .)