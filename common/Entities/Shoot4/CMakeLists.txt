cmake_minimum_required(VERSION 3.14.4)
project(Shoot4 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Shoot4 SHARED
    Shoot4.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Shoot4 PROPERTIES PUBLIC_HEADER Shoot4.hpp)
target_include_directories(Shoot4 PRIVATE .)