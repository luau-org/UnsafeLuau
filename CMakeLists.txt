cmake_minimum_required(VERSION 3.23)
project(UnsafeLuau C)

set(CMAKE_C_STANDARD 99)

add_executable(UnsafeLuau main.c Compiler/ullex.c Compiler/ullex.h)
