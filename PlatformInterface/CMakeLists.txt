project(PlatformInterface_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(PlatformInterface OBJECT ${src_files})

target_include_directories(PlatformInterface PUBLIC "./include")

target_link_libraries(PlatformInterface
  PUBLIC cppcommon
  PUBLIC TestLogging)

# target_sources()
# target_compile_definitions()
# target_compile_features()
# target_compile_options()
# target_link_directories()
# target_link_options()
# target_precompile_headers()
# set_target_properties()
# get_target_property()