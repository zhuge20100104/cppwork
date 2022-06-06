
cmake_minimum_required(VERSION 2.6)

if(APPLE)
    message(STATUS "This is Apple, set boost dir.")
    set(BOOST_DIR /usr/local/Cellar/boost/1.76.0)
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

project(yaml)

add_definitions(-std=c++14)
add_definitions(-g)


find_package(ZLIB)

find_package(OpenCV REQUIRED )

find_package(crossguid REQUIRED)

find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    serialization
    program_options
    thread
    coroutine
    )


if(APPLE)
    MESSAGE(STATUS "This is APPLE, set INCLUDE_DIRS")
set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include /usr/local/iODBC/include /opt/snowflake/snowflakeodbc/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../  ${CMAKE_CURRENT_SOURCE_DIR}/../../../include)
elseif(UNIX)
    MESSAGE(STATUS "This is linux, set INCLUDE_DIRS")
    set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include ${CMAKE_CURRENT_SOURCE_DIR}/../../ ${CMAKE_CURRENT_SOURCE_DIR}/../../../include ${CMAKE_CURRENT_SOURCE_DIR}/../)
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

set(test_file_list ${CMAKE_CURRENT_SOURCE_DIR}/cfg_test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/guid_test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tasks_test.cpp)

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.h    ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp  ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/http/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/img_util/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../tasks/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../tasks/*.h)
foreach( sourcefile ${test_file_list} )
        file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
        string(REPLACE ".cpp" "" file ${filename})
        add_executable(${file}  ${APP_SOURCES})
        target_link_libraries(${file} ${Boost_LIBRARIES} ZLIB::ZLIB ${OpenCV_LIBS})
        target_link_libraries(${file} dl ssl crypto libgtest.a libgtest_main.a pystring libyaml-cpp.a libgmock.a crossguid ${ODBC_LIBS} libnanodbc.a pthread)
endforeach( sourcefile ${test_file_list})
