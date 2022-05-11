
cmake_minimum_required(VERSION 2.6)
project(wd_test)

if(APPLE)
    message(STATUS "This is Apple, set CMAKE_PREFIX_PATH.")
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_PREFIX_PATH  /Users/aabjfzhu/software/vcpkg/ports/cppwork/vcpkg_installed/x64-osx/share)
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)

add_definitions(-w)

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)

find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    serialization
    program_options
    thread
    )


    find_package(ZLIB)

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
set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include /usr/local/iODBC/include /opt/snowflake/snowflakeodbc/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../ ${CURL_INCLUDE_DIR})
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set INCLUDE_DIRS")
    set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif(APPLE)


if(APPLE)
    MESSAGE(STATUS "This is APPLE, set LINK_DIRS")
    set(LINK_DIRS /usr/local/lib /usr/local/iODBC/lib /opt/snowflake/snowflakeodbc/lib/universal /Users/aabjfzhu/software/vcpkg/ports/cppwork/vcpkg_installed/x64-osx/lib)
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

file( GLOB test_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../api_accuracy/utils/io_util.cpp  ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/../../http/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../yaml/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../df/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../death_handler/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../html/impl/*.cpp)

add_library(${PROJECT_NAME}_lib SHARED ${APP_SOURCES} ${test_file})
target_link_libraries(${PROJECT_NAME}_lib ${Boost_LIBRARIES} ZLIB::ZLIB DataFrame::DataFrame ${OpenCV_LIBS} ${CURL_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_lib  ssl crypto libgtest.a pystring libyaml-cpp.a libgmock.a ${ODBC_LIBS} libnanodbc.a pthread dl backtrace html-parser)

foreach( test_file ${test_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${test_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${test_file})
    target_link_libraries(${file} ${PROJECT_NAME}_lib)
endforeach( test_file ${test_file_list})