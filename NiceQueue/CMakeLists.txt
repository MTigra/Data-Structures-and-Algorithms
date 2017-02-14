cmake_minimum_required(VERSION 3.6)
project(NiceQueue)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NiceStack.h NiceQueue.h NiceQueue.hpp NiceStack.hpp)
add_executable(NiceQueue ${SOURCE_FILES})