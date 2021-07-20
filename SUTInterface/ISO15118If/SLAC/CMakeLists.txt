project(SLAC_lib VERSION 1.0.0)

# file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.c" "*.cpp" "*.h")

file(GLOB_RECURSE LIB_HEADER_FILES "tools/*.h" "ether/*.h" "key/*.h" "mme/*.h" "plc/*.h" "slac/*.h")
file(GLOB_RECURSE LIB_SOURCE_FILES "tools/*.c" "ether/*.c" "key/*.c" "mme/*.c" "plc/*.c" "slac/*.c" "slac/*.cpp")

add_library(SLAC OBJECT ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})

# set_source_files_properties(${LIB_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")

target_include_directories(SLAC PUBLIC "./ether" "./key" "./mme" "./plc" "./slac" "./tools")

set_target_properties(SLAC PROPERTIES FOLDER libraries)

target_link_libraries(SLAC PUBLIC cppcommon TestLogging DataType IEC61851If PlatformInterface)