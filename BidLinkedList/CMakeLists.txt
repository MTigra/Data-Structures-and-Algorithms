cmake_minimum_required(VERSION 3.6)
project(BidLinkedList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BidiLinkedList.h BidiLinkedList.hpp demos.hpp)
add_executable(BidLinkedList ${SOURCE_FILES})

# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")