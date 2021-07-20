project(PostConditionFunc_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(PostConditionFunc STATIC ${src_files})

target_include_directories(PostConditionFunc PUBLIC "./include")

target_link_libraries(PostConditionFunc
PUBLIC asio cppcommon fmt openv2g
  PUBLIC  DataType TCP UDP IEC61851If IFRuntime PlatformInterface
          Components TestManagement TestLogging PreconditionFunc LibFunc)