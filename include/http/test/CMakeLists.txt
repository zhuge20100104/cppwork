
cmake_minimum_required(VERSION 2.6)

if(APPLE)
    message(STATUS "This is Apple, do nothing.")
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

project(http_util_test)

add_definitions(-std=c++14)
add_definitions(-g)


find_package(ZLIB)

find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    serialization
    program_options
    thread
    )


if(APPLE)
    MESSAGE(STATUS "This is APPLE, set INCLUDE_DIRS")
    set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include /usr/local/iODBC/include /opt/snowflake/snowflakeodbc/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../)
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set INCLUDE_DIRS")
    set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif(APPLE)


if(APPLE)
    MESSAGE(STATUS "This is APPLE, set LINK_DIRS")
    set(LINK_DIRS /usr/local/lib /usr/local/iODBC/lib /opt/snowflake/snowflakeodbc/lib/universal)
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set LINK_DIRS")
    set(LINK_DIRS ${Boost_INCLUDE_DIRS} /usr/local/lib /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/lib)
endif(APPLE)


include_directories(${INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRS})

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
        file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    
        string(FIND "${filename}"  "test.cpp" "TEMP")
    if( NOT "${TEMP}" STREQUAL "-1" )
        string(REPLACE ".cpp" "" file ${filename})
        add_executable(${file}  ${APP_SOURCES})
        target_link_libraries(${file} ${Boost_LIBRARIES} ZLIB::ZLIB ltdl dl)
        target_link_libraries(${file} ssl crypto libgtest.a libgtest_main.a pystring libgmock.a pthread)
    endif()
endforeach( sourcefile ${APP_SOURCES})