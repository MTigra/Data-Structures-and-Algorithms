cmake_minimum_required(VERSION 3.6)
project(AsInfection)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/grid.cpp
        src/grid.h
        src/main.cpp
        tests/dummy
        contributors.txt
        )

add_executable(AsInfection ${SOURCE_FILES})