add_library(math_functions mysqrt.cpp)

target_include_directories(math_functions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# 系统是否包含log和exp 函数?
include(CheckSymbolExists)
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "math.h" HAVE_EXP)

if(NOT (HAVE_LOG AND HAVE_EXP))
    unset(HAVE_LOG CACHE)
    unset(HAVE_EXP CACHE)
    set(CMAKE_REQUIRED_LIBRARIES "m")
    check_symbol_exists(log "math.h" HAVE_LOG)
    check_symbol_exists(exp "math.h" HAVE_EXP)
    if(HAVE_LOG AND HAVE_EXP)
        target_link_libraries(math_functions PRIVATE m)
    endif()
endif()

# 添加编译选项
if(HAVE_LOG AND HAVE_EXP)
    target_compile_definitions(math_functions PRIVATE "HAVE_LOG" "HAVE_EXP")
endif()

install(TARGETS math_functions DESTINATION lib)
install(FILES math_functions.h DESTINATION include)