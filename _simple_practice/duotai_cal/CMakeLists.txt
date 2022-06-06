cmake_minimum_required(VERSION 2.8)

project(main)

aux_source_directory(. DIR_SRCS)

add_subdirectory(utils)

add_executable(main ${DIR_SRCS})
