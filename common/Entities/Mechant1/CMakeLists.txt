cmake_minimum_required(VERSION 3.14.4)
project(Mechant1 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Mechant1 SHARED
    Mechant1.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Mechant1 PROPERTIES PUBLIC_HEADER Mechant1.hpp)
target_include_directories(Mechant1 PRIVATE .)