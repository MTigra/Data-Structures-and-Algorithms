cmake_minimum_required(VERSION 3.6)
project(SafeArray)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp safearray.h safearray.hpp subject.cpp subject.h)
add_executable(SafeArray ${SOURCE_FILES})