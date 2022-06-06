cmake_minimum_required(VERSION 2.6)

if(APPLE)
    message(STATUS "This is Apple, do nothing.")
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

project(count_ptr)

add_definitions(-std=c++17)

add_definitions(-g)

find_package(ZLIB)

find_package(glog REQUIRED)

find_package(OpenCV REQUIRED )

find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    serialization
    program_options
    thread
    )

find_package(DataFrame REQUIRED)

if(APPLE)
    MESSAGE(STATUS "This is APPLE, set INCLUDE_DIRS")
set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include /usr/local/iODBC/include /opt/snowflake/snowflakeodbc/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ {CMAKE_CURRENT_SOURCE_DIR}/../)
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set INCLUDE_DIRS")
    set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../)
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

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

file( GLOB APP_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/http/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/yaml/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/df/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/death_handler/impl/*.cpp)

add_library(${PROJECT_NAME}_lib SHARED ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME}_lib ${Boost_LIBRARIES} ZLIB::ZLIB glog::glog DataFrame::DataFrame ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME}_lib  ssl crypto libgtest.a pystring libyaml-cpp.a libgmock.a ${ODBC_LIBS} libnanodbc.a pthread dl backtrace)

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file})
    target_link_libraries(${file} ${PROJECT_NAME}_lib)
endforeach( main_file ${main_file_list})