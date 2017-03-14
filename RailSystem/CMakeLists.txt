cmake_minimum_required(VERSION 3.6)
project(RailSystem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        City.h
        main.cpp
        RailSystem.cpp
        RailSystem.h
        Service.h
        services.txt)

add_executable(RailSystem ${SOURCE_FILES})