project(ConfigurationFunc_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(ConfigurationFunc STATIC ${src_files})

target_include_directories(ConfigurationFunc PUBLIC "./include")

target_link_libraries(ConfigurationFunc
PUBLIC asio cppcommon fmt openv2g
  PUBLIC Components DataType TCP UDP IEC61851If IFRuntime PlatformInterface TestManagement TestLogging)