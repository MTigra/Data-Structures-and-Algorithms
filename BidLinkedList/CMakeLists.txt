cmake_minimum_required(VERSION 3.6)
project(BidLinkedList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BidiLinkedList.h BidiLinkedList.hpp demos.hpp)
add_executable(BidLinkedList ${SOURCE_FILES})