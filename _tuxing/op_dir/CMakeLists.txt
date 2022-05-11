cmake_minimum_required(VERSION 2.6)
project(main)

add_definitions(-std=c++11)

aux_source_directory(. CPP_LIST)
find_package(Boost REQUIRED COMPONENTS 
    system
    filesystem
    program_options
    )

include_directories(${Boost_INCLUDE_DIRS} /usr/local/ffmpeg/include)
link_directories(/usr/local/ffmpeg/lib)

add_executable(main ${CPP_LIST})

target_link_libraries(main ${Boost_LIBRARIES})
target_link_libraries(main avutil avformat avcodec)
