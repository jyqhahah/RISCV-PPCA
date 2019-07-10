cmake_minimum_required(VERSION 3.5.2)
project(code)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2  ")

add_executable(code main.cpp parser.hpp decoder.hpp execute.hpp memory.hpp read.hpp writeBack.hpp)