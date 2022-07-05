cmake_minimum_required(VERSION 2.6)

project(3_memory_issue)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O0 -Wall -g -Wno-attributes -fno-omit-frame-pointer")
add_definitions(-g)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)
string(REPLACE ".cpp" "" file "main.cpp")
add_executable(${file}  "main.cpp")
