cmake_minimum_required(VERSION 3.4)
project(covscript)
include_directories(include)

set(CMAKE_CXX_STANDARD 11)

add_executable(test test_linked_list.cpp)