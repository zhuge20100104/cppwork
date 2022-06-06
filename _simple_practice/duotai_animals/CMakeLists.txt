cmake_minimum_required(VERSION 2.6)
project(main)

add_definitions(-std=c++11)

aux_source_directory(. CPP_LIST)

add_subdirectory(utils)

add_executable(main ${CPP_LIST})

target_link_libraries(main util_lib)
