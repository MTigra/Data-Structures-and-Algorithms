cmake_minimum_required(VERSION 3.6)
project(Merge_Sort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp merge_sort.cpp)
add_executable(Merge_Sort ${SOURCE_FILES})