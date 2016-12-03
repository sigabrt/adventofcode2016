cmake_minimum_required(VERSION 2.8)
project(adventofcode2016)

# set(CMAKE_CXX_STANDARD 14)
# set(CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "-std=c++14")

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(day01 day01/main.cpp)
