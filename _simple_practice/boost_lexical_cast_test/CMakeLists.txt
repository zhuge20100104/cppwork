cmake_minimum_required(VERSION 2.6)
project(lexical_cast)

add_definitions(-std=c++14)

include_directories("/opt/local/include")
link_directories("/opt/local/lib")
file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file} ${sourcefile})
    target_link_libraries(${file} boost_filesystem-mt boost_thread-mt boost_system-mt boost_serialization-mt pthread boost_chrono-mt)
endforeach( sourcefile ${APP_SOURCES} )
