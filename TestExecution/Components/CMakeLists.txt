project(Components_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(Components OBJECT ${src_files})

target_include_directories(Components PUBLIC "./include")

target_link_libraries(Components
PUBLIC asio cppcommon fmt openv2g
  PUBLIC Codecs DataType TCP UDP IEC61851If SLAC IFRuntime PlatformInterface TestLogging TestManagement)