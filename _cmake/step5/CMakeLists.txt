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

enable_testing()

# 应用程序能运行吗？
add_test(NAME Runs COMMAND Tutorial 25)
# 使用消息 能工作吗?
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# 定义一个函数来简化添加测试
function(do_test target arg result)
    add_test(NAME Comp${arg} COMMAND ${target} ${arg})
    set_tests_properties(Comp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

# 做基于输出结果的测试
do_test(Tutorial 4 "The sqrt root of 4 is: 2")
do_test(Tutorial 9 "The sqrt root of 9 is: 3")
do_test(Tutorial 5 "The sqrt root of 5 is: 2.23607")
do_test(Tutorial 7 "The sqrt root of 7 is: 2.64575")
do_test(Tutorial 25 "The sqrt root of 25 is: 5")
do_test(Tutorial -25 "The sqrt root of -25 is: 0")
do_test(Tutorial 0.0001 "The sqrt root of 0.0001 is: 0.01")

install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/tutorial_config.h" DESTINATION include)