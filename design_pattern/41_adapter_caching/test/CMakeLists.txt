cmake_minimum_required(VERSION 2.6)
project(adapter_caching)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-g)


find_package(Boost REQUIRED COMPONENTS
    system
    filesystem
    serialization
    program_options
    thread
    )

find_package(OpenCV REQUIRED )
find_package(glog REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} /usr/local/include /usr/local/include/opencv4 /usr/local/iODBC/include /opt/snowflake/snowflakeodbc/include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../ ${CMAKE_CURRENT_SOURCE_DIR}/../include/ ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/)

LINK_DIRECTORIES(/usr/local/lib /usr/local/iODBC/lib /opt/snowflake/snowflakeodbc/lib/universal)

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/death_handler/impl/*.cpp) 
foreach( sourcefile ${APP_SOURCES} )
        file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})
    
        string(FIND "${filename}"  "test.cpp" "TEMP")
    if( NOT "${TEMP}" STREQUAL "-1" )
        string(REPLACE ".cpp" "" file ${filename})
        add_executable(${file}  ${APP_SOURCES})
        target_link_libraries(${file} ${Boost_LIBRARIES} ${OpenCV_LIBS})
        target_link_libraries(${file} glog::glog ssl crypto libgtest.a libgmock.a iodbc iodbcinst libnanodbc.a pthread)
    endif()
endforeach( sourcefile ${APP_SOURCES})