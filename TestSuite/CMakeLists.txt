project(TestSuite_lib VERSION 1.0.0)

# get all .cpp file in src directory
file(GLOB_RECURSE src_files LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.cpp")

foreach(item ${src_files})
  string(REGEX REPLACE ".*/([a-zA-Z0-9_]+).cpp" "\\1" target_test ${item})
  message(STATUS "BUILD TARGET: ${target_test} - ${item}")
  add_executable(${target_test} ${item})

  target_include_directories(${target_test} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" ${INCLUDE_DIRECTORIES})
  target_link_libraries(${target_test} PUBLIC fmt asio cppcommon openv2g
                                              Codecs DataType PlatformInterface IFRuntime TCP UDP SLAC IEC61851If
                                              Components CmnFunc ConfigurationFunc PreconditionFunc TestBehaviorFunc PostConditionFunc
                                              TestManagement TestLogging TestCase)
  target_compile_definitions(${target_test} PUBLIC BOOST_THREAD_USE_LIB)
endforeach()