project(IFRuntime_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(IFRuntime OBJECT ${src_files})

target_include_directories(IFRuntime PUBLIC "./include")

target_link_libraries(IFRuntime
PUBLIC cppcommon TestLogging)