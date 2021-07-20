project(TLS_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(TLS OBJECT ${src_files})

target_include_directories(TLS PUBLIC "./include")

target_link_libraries(TLS
  PRIVATE asio cppcommon DataType fmt)