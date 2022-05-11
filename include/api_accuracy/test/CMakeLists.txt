cmake_minimum_required(VERSION 2.6)

if(APPLE)
    message(STATUS "This is Apple, do nothing.")
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_PREFIX_PATH /Users/aabjfzhu/software/vcpkg/ports/cppwork/vcpkg_installed/x64-osx/share )
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

project(app_perf_test)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-g)

find_package(ZLIB)

find_package(glog REQUIRED)

find_package(OpenCV REQUIRED )

find_package(OpenSSL REQUIRED)

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

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../utils/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../cases/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/../../http/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../yaml/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../df/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../death_handler/impl/*.cpp)

add_library(${PROJECT_NAME}_lib SHARED ${APP_SOURCES} ${test_file})
target_link_libraries(${PROJECT_NAME}_lib ${Boost_LIBRARIES} ZLIB::ZLIB glog::glog DataFrame::DataFrame ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME}_lib OpenSSL::SSL OpenSSL::Crypto libgtest.a pystring libyaml-cpp.a libgmock.a ${ODBC_LIBS} libnanodbc.a pthread dl backtrace)

foreach( test_file ${test_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${test_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${test_file})
    target_link_libraries(${file} ${PROJECT_NAME}_lib)
endforeach( test_file ${test_file_list})