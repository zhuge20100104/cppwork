aux_source_directory(. utils)

add_definitions(-std=c++11)
add_library(util_lib ${utils})
