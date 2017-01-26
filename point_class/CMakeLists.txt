cmake_minimum_required(VERSION 3.6)
project(point_class)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp xipoint.cpp)
add_executable(point_class ${SOURCE_FILES})