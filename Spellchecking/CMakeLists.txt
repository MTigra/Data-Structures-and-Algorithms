cmake_minimum_required(VERSION 3.7)
project(Spellchecking)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dictionary.h hashset.h hashset.cpp wordlist.txt test.txt)
add_executable(Spellchecking ${SOURCE_FILES})