if(NOT TARGET cppcommon)

# CMake searches for a file called Find<PackageName>.cmake in CMAKE_MODULE_PATH
# directories specifying a search path for CMake modules to be loaded by the
# include() or find_package() commands before checking the default modules that come with CMake. By default it is empty, it is intended to be set by the project.

  find_package(Threads REQUIRED)
  if(UNIX AND NOT APPLE AND NOT MSYS)
    # In Module mode, CMake searches for a file called Find<PackageName>.cmake.
    # The file is first searched in the CMAKE_MODULE_PATH, then among the
    # Find Modules provided by the CMake installation. If the file is found,
    # it is read and processed by CMake. It is responsible for finding the package,
    # checking the version, and producing any needed messages
    #find_package(LibBFD QUIET)
    find_package(LibDL QUIET)
    find_package(LibRT QUIET)
    find_package(LibUUID QUIET)
  endif()
  if(WIN32 OR MSYS)
    find_package(DbgHelp QUIET)
    find_package(RPC QUIET)
    find_package(Userenv QUIET)
  endif()
  list(APPEND LINKLIBS Threads::Threads)
  if(UNIX AND NOT APPLE AND NOT MSYS)
    #list(APPEND LINKLIBS ${LIBBFD_LIBRARIES})
    list(APPEND LINKLIBS ${LIBDL_LIBRARIES})
    list(APPEND LINKLIBS ${LIBRT_LIBRARIES})
    list(APPEND LINKLIBS ${LIBUUID_LIBRARIES})
  endif()
  if(WIN32 OR MSYS)
    list(APPEND LINKLIBS ${DBGHELP_LIBRARIES})
    list(APPEND LINKLIBS ${RPC_LIBRARIES})
    list(APPEND LINKLIBS ${USERENV_LIBRARIES})
    list(APPEND LINKLIBS ${LIBVLD_LIBRARIES})
  endif()

  # Library
  file(GLOB_RECURSE LIB_HEADER_FILES "cppcommon/include/*.h")
  file(GLOB_RECURSE LIB_INLINE_FILES "cppcommon/include/*.inl")
  file(GLOB_RECURSE LIB_SOURCE_FILES
    "cppcommon/src/errors/*.cpp"
    "cppcommon/src/system/*.cpp"
    "cppcommon/src/memory/*.cpp"
    "cppcommon/src/threads/*.cpp"
    "cppcommon/src/time/*.cpp"
    "cppcommon/src/asiowrapper/*.cpp"
    "cppcommon/src/filesystem/*.cpp"
    "cppcommon/src/common/*.cpp"
  )
  set_source_files_properties(${LIB_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
  add_library(cppcommon ${LIB_HEADER_FILES} ${LIB_INLINE_FILES} ${LIB_SOURCE_FILES})
  target_include_directories(cppcommon PUBLIC "cppcommon/include" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" PUBLIC ${vld})
  target_link_libraries(cppcommon ${LINKLIBS} fmt asio)
  set_target_properties(cppcommon PROPERTIES FOLDER libraries)
  list(APPEND INSTALL_TARGETS cppcommon)
  list(APPEND LINKLIBS cppcommon)

endif()
