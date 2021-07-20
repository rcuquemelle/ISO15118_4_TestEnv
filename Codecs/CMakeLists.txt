project(Codecs_lib VERSION 1.0.0)

file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(Codecs OBJECT ${src_files})

target_include_directories(Codecs
PUBLIC
  "./include/messages"
  "./include")

target_link_libraries(Codecs PUBLIC openv2g asio DataType TestLogging)