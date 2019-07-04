cmake_minimum_required(VERSION 3.13)
project(RISCV)

set(CMAKE_CXX_STANDARD 14)

add_executable(RISCV main.cpp parser.hpp decoder.hpp execute.hpp memory.hpp read.hpp writeBack.hpp)