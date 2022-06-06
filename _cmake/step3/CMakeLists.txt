cmake_minimum_required(VERSION 3.10)

# 设置工程名称和版本
project(Tutorial VERSION 1.0)

# 指定C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# 是否使用自定义的 math实现
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# 配置生成header文件
configure_file(tutorial_config.h.in tutorial_config.h)

# 添加 math_functions 库
if(USE_MYMATH)
    add_subdirectory(math_functions)
    list(APPEND EXTRA_LIBS math_functions)
endif()

add_executable(Tutorial tutorial.cpp)

target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")
