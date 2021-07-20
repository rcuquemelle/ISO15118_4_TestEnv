if(NOT TARGET fmt)

  # Module library
  file(GLOB_RECURSE LIB_HEADER_FILES "fmt/include/*.h")
  file(GLOB_RECURSE LIB_INLINE_FILES "fmt/include/*.inl")
  file(GLOB_RECURSE LIB_SOURCE_FILES "fmt/src/*.cc")
  add_library(fmt ${LIB_SOURCE_FILES} ${LIB_HEADER_FILES} ${LIB_INLINE_FILES})
  target_include_directories(fmt PUBLIC "fmt/include")

  # Module folder
  set_target_properties(fmt PROPERTIES FOLDER modules/fmt)

endif()
