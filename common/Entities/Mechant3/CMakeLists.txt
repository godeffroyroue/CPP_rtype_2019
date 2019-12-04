cmake_minimum_required(VERSION 3.14.4)
project(Mechant3 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Mechant3 SHARED
    Mechant3.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Mechant3 PROPERTIES PUBLIC_HEADER Mechant3.hpp)
target_include_directories(Mechant3 PRIVATE .)