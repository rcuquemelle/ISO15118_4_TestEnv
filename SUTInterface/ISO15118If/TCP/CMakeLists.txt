project(TCP_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(TCP OBJECT ${src_files})

target_include_directories(TCP PUBLIC "./include")

target_link_libraries(TCP
PUBLIC cppcommon TestLogging)