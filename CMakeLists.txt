cmake_minimum_required(VERSION 3.5.2)
project(RISCV)

set(CMAKE_CXX_STANDARD 14)

add_executable(RISCV main.cpp parser.hpp decoder.hpp execute.hpp memory.hpp read.hpp writeBack.hpp)