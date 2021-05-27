cmake_minimum_required(VERSION 3.0.0)
project(lc VERSION 0.1.0)

include_directories(./include)
include_directories(./src)
set(CXX_STANDARD 17)
add_executable(lc main.cpp)
