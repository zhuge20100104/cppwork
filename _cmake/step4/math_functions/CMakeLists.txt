add_library(math_functions mysqrt.cpp)

target_include_directories(math_functions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS math_functions DESTINATION lib)
install(FILES math_functions.h DESTINATION include)