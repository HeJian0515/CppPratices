cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB srcs ./*.cpp ./*.c)

foreach(src IN ITEMS ${srcs})
    get_filename_component(main_name ${src} NAME_WE)
    add_executable(${main_name} ${src})
endforeach()