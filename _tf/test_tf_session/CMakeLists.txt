cmake_minimum_required(VERSION 3.3)


project(test_tf_session)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${INCLUDE_DIRS})

find_package(TensorflowCC REQUIRED)

file( GLOB test_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../../include/tf_/impl/tensor_testutil.cc ${CMAKE_CURRENT_SOURCE_DIR}/../../include/death_handler/impl/*.cpp)

add_library(${PROJECT_NAME}_lib SHARED ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME}_lib PUBLIC ${CONAN_LIBS} TensorflowCC::TensorflowCC)

foreach( test_file ${test_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${test_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${test_file})
    target_link_libraries(${file} PUBLIC ${PROJECT_NAME}_lib)
endforeach( test_file ${test_file_list})
