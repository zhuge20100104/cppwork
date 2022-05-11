cmake_minimum_required(VERSION 2.6)
project(main)

add_definitions(-std=c++11)

aux_source_directory(. CPP_LIST)

find_package(Boost REQUIRED COMPONENTS 
    system
    filesystem
    )

include_directories(${Boost_INCLUDE_DIRS})


add_executable(main ${CPP_LIST})

target_link_libraries(main ${Boost_LIBRARIES})
