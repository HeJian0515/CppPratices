cmake_minimum_required(VERSION 3.30)
project(gs_common)

find_package(spdlog CONFIG REQUIRED)

add_library(gs_common SHARED
        log/Log.cpp)

target_link_libraries(gs_common
        PUBLIC
        spdlog::spdlog
)