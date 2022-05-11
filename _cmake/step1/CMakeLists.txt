cmake_minimum_required(VERSION 3.10)

# 设置工程名称和版本
project(Tutorial VERSION 1.0)

# 指定C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# 配置生成header文件
configure_file(tutorial_config.h.in tutorial_config.h)

add_executable(Tutorial tutorial.cpp)

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")
