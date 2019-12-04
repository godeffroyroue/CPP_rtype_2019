cmake_minimum_required(VERSION 3.14.4)
project(Mechant4 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Mechant4 SHARED
    Mechant4.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Mechant4 PROPERTIES PUBLIC_HEADER Mechant4.hpp)
target_include_directories(Mechant4 PRIVATE .)