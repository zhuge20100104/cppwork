cmake_minimum_required(VERSION 2.6)
project(chat_room)

add_definitions(-std=c++14)

include_directories("/usr/local/include")
link_directories("/usr/local/lib")
add_executable(main main.cpp)
target_link_libraries(main boost_filesystem boost_thread boost_system boost_serialization pthread)

