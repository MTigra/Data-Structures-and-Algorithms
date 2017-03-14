cmake_minimum_required(VERSION 3.6)
project(SCC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SCCSolver.cpp)
add_executable(SCC ${SOURCE_FILES})