project(PreconditionFunc_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(PreconditionFunc STATIC ${src_files})

target_include_directories(PreconditionFunc PUBLIC "./include")

target_link_libraries(PreconditionFunc
PUBLIC asio cppcommon fmt openv2g
  PUBLIC Components DataType TCP UDP IEC61851If IFRuntime PlatformInterface
  CmnFunc TestManagement TestLogging ConfigurationFunc TestBehaviorFunc LibFunc)