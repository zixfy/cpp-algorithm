cmake_minimum_required(VERSION 3.22)
project(cpp_algorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_advanced_container_template main.cpp)

file(GLOB test_src "./test/*.cpp")
foreach(source ${test_src})
    message(STATUS "using test file: ${source}")
    get_filename_component(filename ${source} NAME)
    add_executable(${filename} ${source}
            main.cpp
            util/container_printer.hpp)
endforeach()