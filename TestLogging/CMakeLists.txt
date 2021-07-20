project(TestLogging_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(TestLogging OBJECT ${src_files})

target_include_directories(TestLogging PUBLIC "./include")

target_link_libraries(TestLogging PUBLIC cppcommon asio fmt)
