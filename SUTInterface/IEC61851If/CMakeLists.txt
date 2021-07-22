project(IEC61851If_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.c" "*.h")

add_library(IEC61851If OBJECT ${src_files})

target_include_directories(IEC61851If PUBLIC "./include")

target_link_options(IEC61851If INTERFACE "LINKER:-lpigpiod_if2,-lrt")

target_link_libraries(IEC61851If
PUBLIC cppcommon DataType TestLogging PlatformInterface)