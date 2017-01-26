cmake_minimum_required(VERSION 3.6)
project(Compression)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_FILES main.cpp utilities.cpp utilities.h huffman.cpp huffman.h shannon-fano.h shannon-fano.cpp)
add_executable(Compression ${SOURCE_FILES})