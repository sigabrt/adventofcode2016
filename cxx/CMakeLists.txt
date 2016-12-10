cmake_minimum_required(VERSION 2.8)
project(adventofcode2016)

# The stupid old version of CMake provided by Travis doesn't support this
# set(CMAKE_CXX_STANDARD 14)
# set(CXX_STANDARD_REQUIRED TRUE)

# So I'm forced to do this instead
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror")

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(day01 day01/main.cpp)
add_executable(day02 day02/main.cpp)
