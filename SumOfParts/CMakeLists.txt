cmake_minimum_required(VERSION 3.7)
project(SumOfParts)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp parts.cpp parts.h definitions.txt queries.txt)
add_executable(SumOfParts ${SOURCE_FILES})