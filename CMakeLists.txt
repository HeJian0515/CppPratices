cmake_minimum_required(VERSION 3.30)
project(lc VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(./include)
include_directories(./src)

# 包含sbin里的CMakeLists
add_subdirectory(sbin)

add_executable(lc main.cpp)