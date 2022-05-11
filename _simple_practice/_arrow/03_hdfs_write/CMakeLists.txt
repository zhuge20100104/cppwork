cmake_minimum_required(VERSION 2.6)
project(lexical_cast)

add_definitions(-std=c++14)
set( ENV{ARROW_LIBHDFS_DIR} /opt/hadoop-2.10.1/lib/native )

include_directories("/usr/local/include" "/usr/include")
link_directories("/usr/local/lib" "/usr/lib/x86_64-linux-gnu" "/opt/hadoop-2.10.1/lib/native")
file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file} ${sourcefile})
    target_link_libraries(${file} boost_filesystem boost_thread boost_system boost_serialization pthread boost_chrono arrow parquet hdfs)
endforeach( sourcefile ${APP_SOURCES} )

