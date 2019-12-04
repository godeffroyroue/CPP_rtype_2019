cmake_minimum_required(VERSION 3.14.4)
project(Shoot2 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Shoot2 SHARED
    Shoot2.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Shoot2 PROPERTIES PUBLIC_HEADER Shoot2.hpp)
target_include_directories(Shoot2 PRIVATE .)