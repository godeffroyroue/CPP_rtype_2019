cmake_minimum_required(VERSION 3.14.4)
project(Mechant2 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Mechant2 SHARED
    Mechant2.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Mechant2 PROPERTIES PUBLIC_HEADER Mechant2.hpp)
target_include_directories(Mechant2 PRIVATE .)