cmake_minimum_required(VERSION 3.30)
project(gs_common)

find_package(spdlog CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)

add_library(gs_common SHARED
        log/Log.cpp
        net/Session.cpp
)

target_link_libraries(gs_common
        PUBLIC
        spdlog::spdlog

        PRIVATE
        asio::asio
)