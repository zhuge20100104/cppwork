cmake_minimum_required(VERSION 2.6)
project(chat_room)

add_definitions(-std=c++14)


find_package(Boost REQUIRED COMPONENTS 
    system
    filesystem
    serialization
    )

include_directories(${Boost_INCLUDE_DIRS})

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    if( NOT ${filename} MATCHES "parse_msg.cpp" )
        string(REPLACE ".cpp" "" file ${filename})
        add_executable(${file} ${sourcefile} "parse_msg.cpp")
        target_link_libraries(${file} ${Boost_LIBRARIES})
        target_link_libraries(${file} pthread)
    endif( NOT ${filename} MATCHES "struct_header.cpp" )
endforeach( sourcefile ${APP_SOURCES} )

