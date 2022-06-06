cmake_minimum_required(VERSION 2.6)

project(non_overlapping_interval)
set(CMAKE_CXX_STANDARD 20)
add_definitions(-g)

string(REPLACE ".cpp" "" file "main.cpp")
add_executable(${file}  "main.cpp")
