cmake_minimum_required(VERSION 3.10)
project(SubOctaveForBass)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-march=native)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LV2 REQUIRED lv2)

#include_directories(kfr/include)
include_directories(${LV2_INCLUDE_DIRS})

add_library(SubOctaveForBass SHARED src/main.cpp)
set_target_properties(SubOctaveForBass PROPERTIES PREFIX "")
