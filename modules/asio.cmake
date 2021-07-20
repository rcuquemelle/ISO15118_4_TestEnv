if(NOT TARGET asio)

  find_package(Threads REQUIRED)
  list(APPEND LINKLIBS Threads::Threads)
  # Module library
  file(GLOB LIB_SOURCE_FILES FOLLOW_SYMLINKS "asio/asio/src/*.cpp")
  add_library(asio ${LIB_SOURCE_FILES})
  target_compile_definitions(asio PUBLIC ASIO_ENABLE_BOOST ASIO_SEPARATE_COMPILATION) #ASIO_HAS_BOOST_BIND
  target_include_directories(asio PUBLIC "asio/asio/include" PUBLIC ${OPENSSL_INCLUDE_DIR})
  target_link_libraries(asio ${OPENSSL_LIBRARIES} -lpthread)

  # Module folder
  set_target_properties(asio PROPERTIES FOLDER modules/asio)

endif()
