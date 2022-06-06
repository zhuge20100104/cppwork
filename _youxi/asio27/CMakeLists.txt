cmake_minimum_required(VERSION 2.6)
project(chat_room)

add_definitions(-std=c++14)


find_package(Boost REQUIRED COMPONENTS 
    system
    filesystem
    serialization
    program_options
    )

include_directories(${Boost_INCLUDE_DIRS} "/usr/local/Cellar/protobuf/3.17.3/include")
link_directories("/usr/local/Cellar/protobuf/3.17.3/lib")

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    if( NOT ${filename} MATCHES "parse_msg.cpp")
        string(REPLACE ".cpp" "" file ${filename})
        add_executable(${file} ${sourcefile} "parse_msg.cpp" "Protocal.pb.cc")
        target_link_libraries(${file} ${Boost_LIBRARIES})
        target_link_libraries(${file} pthread)
        target_link_libraries(${file} protobuf)
    endif( NOT ${filename} MATCHES "parse_msg.cpp" )
endforeach( sourcefile ${APP_SOURCES} )

