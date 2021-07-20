project(DataType_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(DataType OBJECT ${src_files})

target_include_directories(DataType PUBLIC "./include")

target_link_libraries(DataType PUBLIC openv2g)