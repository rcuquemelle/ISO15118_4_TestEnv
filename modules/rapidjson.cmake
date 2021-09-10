if(NOT TARGET rapidjson)

add_library(rapidjson INTERFACE)
target_include_directories(rapidjson INTERFACE "./rapidjson")

endif()