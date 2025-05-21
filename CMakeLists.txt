cmake_minimum_required(VERSION 3.30)
project(main VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(./include)
include_directories(./src)

# 包含sbin里的CMakeLists
add_subdirectory(sbin)

add_executable(main main.cpp)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(main PRIVATE fmt::fmt-header-only)
find_package(Microsoft.GSL CONFIG REQUIRED)
target_link_libraries(main PRIVATE Microsoft.GSL::GSL)