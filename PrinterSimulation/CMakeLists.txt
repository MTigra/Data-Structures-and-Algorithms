cmake_minimum_required(VERSION 3.6)
project(PrinterSimulation)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        arbitrary.out
        arbitrary.run
        bigfirst.out
        bigfirst.run
        event.cpp
        event.h
        job.cpp
        job.h
        main.cpp
        simulator.cpp
        fifo.h
        fifo.cpp
        simulator.h
        small.out
        small.run)

add_executable(PrinterSimulation ${SOURCE_FILES})