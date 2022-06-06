
cmake_minimum_required(VERSION 2.6)

project(hello_world)

add_definitions(-std=c++14)
add_definitions(-g)



find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    serialization
    program_options
    thread
    )

include_directories(${Boost_INCLUDE_DIRS} /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../include)

LINK_DIRECTORIES(/usr/local/lib)

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/http/impl/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
        file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    if( "${filename}" STREQUAL "main.cpp")
        string(REPLACE ".cpp" "" file ${filename})
        add_executable(${file}  ${APP_SOURCES})
        target_link_libraries(${file} ${Boost_LIBRARIES})
        target_link_libraries(${file} pthread ssl crypto libgtest.a libgmock.a iodbc iodbcinst libnanodbc.a pystring pthread)
    endif()
endforeach( sourcefile ${APP_SOURCES})