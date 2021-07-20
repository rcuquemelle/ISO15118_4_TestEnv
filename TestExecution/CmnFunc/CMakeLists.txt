project(CmnFunc_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(CmnFunc STATIC ${src_files})

target_include_directories(CmnFunc PUBLIC "./include")

target_link_libraries(CmnFunc
PUBLIC asio cppcommon fmt openv2g
  PUBLIC Codecs DataType Components TCP UDP IEC61851If IFRuntime PlatformInterface TestLogging)
  