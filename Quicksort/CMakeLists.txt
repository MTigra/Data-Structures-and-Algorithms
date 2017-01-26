cmake_minimum_required(VERSION 3.6)
project(Quicksort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp quick_sort.cpp)
add_executable(Quicksort ${SOURCE_FILES})