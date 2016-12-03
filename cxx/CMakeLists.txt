cmake_minimum_required(VERSION 3.1)
project(adventofcode2016)

set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED TRUE)

configure_file(cxx/config.h.in cxx/config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(day01 cxx/day01/main.cpp)
