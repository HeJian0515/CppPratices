cmake_minimum_required(VERSION 4.0)
project(cpp20)

find_package(cppcoro CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp20 main.cpp)

add_executable(coroTest coro.cpp)
target_link_libraries(coroTest PRIVATE cppcoro)

add_executable(spaceOpTest spaceship_op.cpp)