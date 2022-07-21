cmake_minimum_required(VERSION 3.5)
project(AKFSFSimulation)

set(CMAKE_CXX_STANDARD 11)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)


include_directories(/usr/include/eigen3)
link_directories(${CMAKE_BINARY_DIR})

set(filter_file_list 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kalmanfilter_lkf.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kalmanfilter_ekf.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kalmanfilter_ukf.cpp)

set(SRC_CPP
    src/display.cpp
    src/beacons.cpp
    src/sensors.cpp
    src/simulation.cpp
    src/utils.cpp
)

add_library(${PROJECT_NAME}_lib SHARED ${SRC_CPP})
target_link_libraries(${PROJECT_NAME}_lib
        SDL2
        SDL2_ttf
        Eigen3::Eigen
)

foreach(filter_file ${filter_file_list})
        file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR}/src ${filter_file})
        string(REPLACE ".cpp" "" bin_file ${filename})

        add_executable(${bin_file}
                ${filter_file} src/main.cpp
        )

        target_link_libraries(${bin_file}
                ${PROJECT_NAME}_lib
        )
endforeach(filter_file ${filter_file_list})

add_custom_command(TARGET ${PROJECT_NAME}_lib PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:${PROJECT_NAME}_lib>)