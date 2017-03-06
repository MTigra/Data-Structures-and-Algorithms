cmake_minimum_required(VERSION 3.6)
project(ParkingLot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp car.cpp car.h)
add_executable(ParkingLot ${SOURCE_FILES})