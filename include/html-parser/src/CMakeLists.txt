cmake_minimum_required(VERSION 3.0)
project(html-parser)

set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

if(APPLE)
    message(STATUS "This is Apple, set CMAKE_PREFIX_PATH.")
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_PREFIX_PATH  /Users/aabjfzhu/software/vcpkg/ports/cppwork/vcpkg_installed/x64-osx/share)
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /home/fredric/software/vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)


if(APPLE)
    MESSAGE(STATUS "This is APPLE, set INCLUDE_DIRS")
set(INCLUDE_DIRS ${Boost_INCLUDE_DIRS} /usr/local/include /usr/local/iODBC/include /opt/snowflake/snowflakeodbc/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../)
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

find_package(glog REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file( GLOB APP_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h) 

# Remove test files from app sources
list(REMOVE_ITEM APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cc")
message(STATUS "${APP_SOURCES}")

add_library(${PROJECT_NAME} SHARED ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME} glog::glog)
add_library(${PROJECT_NAME}_static STATIC ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME}_static glog::glog)

INSTALL (TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
INSTALL (FILES ${APP_HEADERS} DESTINATION include/${PROJECT_NAME})
