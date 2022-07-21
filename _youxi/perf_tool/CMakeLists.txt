cmake_minimum_required(VERSION 2.6)

if(APPLE)
    message(STATUS "This is Apple, do nothing.")
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

project(perf_tool)

add_definitions(-std=c++14)
add_definitions(-g)

set(BOOST_DIR /usr/local/Cellar/boost/1.76.0)
find_package(Boost REQUIRED COMPONENTS 
    system
    filesystem
    serialization
    program_options
    coroutine
    thread
    )

find_package(crossguid REQUIRED)
find_package(ZLIB)

if(APPLE)
    MESSAGE(STATUS "This is APPLE, set INCLUDE_DIRS")
    set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../../include /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../../ ${CMAKE_CURRENT_SOURCE_DIR}/utils)
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set INCLUDE_DIRS")
    set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include ${CMAKE_CURRENT_SOURCE_DIR}/utils)
endif(APPLE)


if(APPLE)
    MESSAGE(STATUS "This is APPLE, set LINK_DIRS")
    set(LINK_DIRS /usr/local/lib /usr/local/iODBC/lib /opt/snowflake/snowflakeodbc/lib/universal)
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set LINK_DIRS")
    set(LINK_DIRS ${Boost_INCLUDE_DIRS} /usr/local/lib /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/lib)
endif(APPLE)

if(APPLE)
    MESSAGE(STATUS "This is APPLE, set ODBC_LIBS")
    set(ODBC_LIBS iodbc iodbcinst)
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set LINK_DIRS")
    set(ODBC_LIBS odbc odbcinst ltdl)
endif(APPLE)


include_directories(${INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRS})

set(main_file_list "${CMAKE_CURRENT_SOURCE_DIR}/server.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/master.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/slave.cpp")

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tasks/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.h ${CMAKE_CURRENT_SOURCE_DIR}/tasks/*.h ${CMAKE_CURRENT_SOURCE_DIR}/../../include/http/impl/*.cpp)

list(REMOVE_ITEM APP_SOURCES ${main_file_list})

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR}/src ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file} ${APP_SOURCES} ${main_file})
    target_link_libraries(${file} ${Boost_LIBRARIES} ZLIB::ZLIB crossguid pystring)
    target_link_libraries(${file} dl ssl crypto pthread)
endforeach( main_file ${main_file_list} )

