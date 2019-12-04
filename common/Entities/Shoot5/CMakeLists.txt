cmake_minimum_required(VERSION 3.14.4)
project(Shoot5 VERSION 0.1 DESCRIPTION "A small differential compression library")
add_library(Shoot5 SHARED
    Shoot5.cpp
    ../../src/AEntity.cpp
)
set_target_properties(Shoot5 PROPERTIES PUBLIC_HEADER Shoot5.hpp)
target_include_directories(Shoot5 PRIVATE .)