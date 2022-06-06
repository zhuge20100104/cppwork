cmake_minimum_required(VERSION 3.3)


project(tf_fashion_predict)

set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig/")

set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(TensorflowCC REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(PKG_PARQUET REQUIRED IMPORTED_TARGET parquet)
pkg_search_module(PKG_ARROW REQUIRED IMPORTED_TARGET arrow)
pkg_search_module(PKG_ARROW_COMPUTE REQUIRED IMPORTED_TARGET arrow-compute)
pkg_search_module(PKG_ARROW_CSV REQUIRED IMPORTED_TARGET arrow-csv)
pkg_search_module(PKG_ARROW_DATASET REQUIRED IMPORTED_TARGET arrow-dataset)
pkg_search_module(PKG_ARROW_FS REQUIRED IMPORTED_TARGET arrow-filesystem)
pkg_search_module(PKG_ARROW_JSON REQUIRED IMPORTED_TARGET arrow-json)

set(ARROW_INCLUDE_DIRS ${PKG_PARQUET_INCLUDE_DIRS} ${PKG_ARROW_INCLUDE_DIRS} ${PKG_ARROW_COMPUTE_INCLUDE_DIRS} ${PKG_ARROW_CSV_INCLUDE_DIRS} ${PKG_ARROW_DATASET_INCLUDE_DIRS} ${PKG_ARROW_FS_INCLUDE_DIRS} ${PKG_ARROW_JSON_INCLUDE_DIRS})

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../include ${ARROW_INCLUDE_DIRS})

set(ARROW_LIBS PkgConfig::PKG_PARQUET PkgConfig::PKG_ARROW PkgConfig::PKG_ARROW_COMPUTE PkgConfig::PKG_ARROW_CSV PkgConfig::PKG_ARROW_DATASET PkgConfig::PKG_ARROW_FS PkgConfig::PKG_ARROW_JSON)

include_directories(${INCLUDE_DIRS})


file( GLOB test_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../../include/tf_/impl/tensor_testutil.cc ${CMAKE_CURRENT_SOURCE_DIR}/../../include/tf_/impl/queue_runner.cc ${CMAKE_CURRENT_SOURCE_DIR}/../../include/tf_/impl/coordinator.cc ${CMAKE_CURRENT_SOURCE_DIR}/../../include/tf_/impl/status.cc ${CMAKE_CURRENT_SOURCE_DIR}/../../include/death_handler/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/df/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/arr_/impl/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../../include/img_util/impl/*.cpp)

add_library(${PROJECT_NAME}_lib SHARED ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME}_lib PUBLIC ${CONAN_LIBS} TensorflowCC::TensorflowCC ${ARROW_LIBS})

foreach( test_file ${test_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${test_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${test_file})
    target_link_libraries(${file} PUBLIC ${PROJECT_NAME}_lib)
endforeach( test_file ${test_file_list})
