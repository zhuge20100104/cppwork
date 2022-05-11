cmake_minimum_required(VERSION 3.5)
project(webdriverxx)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
                  DESTINATION include/${PROJECT_NAME}
                  FILES_MATCHING PATTERN "*")