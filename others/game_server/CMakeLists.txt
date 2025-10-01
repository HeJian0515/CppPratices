cmake_minimum_required(VERSION 3.31)
project(game_server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置库和可执行文件的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src/common)

find_package(Lua REQUIRED)

target_include_directories(gs_common PUBLIC src/common)

add_executable(game_server main.cpp
        src/lua/lua_main.cpp)
target_link_libraries(game_server
        PRIVATE gs_common
        PRIVATE ${LUA_LIBRARIES}
)

add_executable(lua_test src/lua/lua_main.cpp)
target_link_libraries(lua_test
        PRIVATE ${LUA_LIBRARIES}
)