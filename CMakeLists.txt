cmake_minimum_required(VERSION 3.10)
project(SubOctaveForBass)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-march=native)

# LV2 헤더 찾기
find_package(PkgConfig REQUIRED)
pkg_check_modules(LV2 REQUIRED lv2)

# KFR 포함 (kfr 폴더가 프로젝트 루트에 있다고 가정)
#include_directories(kfr/include)
include_directories(${LV2_INCLUDE_DIRS})

# 공유 라이브러리(.so) 생성
add_library(SubOctaveForBass SHARED src/main.cpp)
set_target_properties(SubOctaveForBass PROPERTIES PREFIX "")
