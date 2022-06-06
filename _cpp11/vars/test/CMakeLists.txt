
cmake_minimum_required(VERSION 2.6)
project(vars_test)

add_definitions(-std=c++14)
add_definitions(-g)



find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    serialization
    program_options
    thread
    )

include_directories(${Boost_INCLUDE_DIRS} /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../../)

LINK_DIRECTORIES(/usr/local/lib)

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
        file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    
        string(FIND "${filename}"  "test.cpp" "TEMP")
    if( NOT "${TEMP}" STREQUAL "-1" )
        string(REPLACE ".cpp" "" file ${filename})
        add_executable(${file}  ${APP_SOURCES})
        target_link_libraries(${file} ${Boost_LIBRARIES})
        target_link_libraries(${file}  ssl crypto libgtest.a libgtest_main.a libgmock.a pthread)
    endif()
endforeach( sourcefile ${APP_SOURCES})