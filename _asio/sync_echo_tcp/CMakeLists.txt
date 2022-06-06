cmake_minimum_required(VERSION 2.6)
project(chat_room)

add_definitions(-std=c++14)

include_directories("/usr/local/include")
link_directories("/usr/local/lib")
file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file} ${sourcefile})
    target_link_libraries(${file} boost_filesystem boost_thread boost_system boost_serialization pthread)
endforeach( sourcefile ${APP_SOURCES} )

