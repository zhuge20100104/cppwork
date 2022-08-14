cmake_minimum_required(VERSION 2.6)

project(bm1_reverse_list)
set(CMAKE_CXX_STANDARD 20)
add_definitions(-g)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)
string(REPLACE ".cpp" "" file "main.cpp")
add_executable(${file}  "main.cpp")
