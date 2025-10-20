cmake_minimum_required(VERSION 3.8)
project(skrf_test_2)

set(CMAKE_CXX_STANDARD 98)

# Force build artifacts into current source directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(skrf_test_2 ${CMAKE_SOURCE_DIR}/main.cpp)

