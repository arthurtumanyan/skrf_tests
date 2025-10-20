cmake_minimum_required(VERSION 3.8)
project(skrf_test_c C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(skrf_test_c main.c)
