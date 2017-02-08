cmake_minimum_required(VERSION 3.6)
project(DNA_linked_list)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dna_element.h linked_list.h linked_list.hpp dna_element.cpp dna_repairer.cpp dna_repairer.h)
add_executable(DNA_linked_list ${SOURCE_FILES})