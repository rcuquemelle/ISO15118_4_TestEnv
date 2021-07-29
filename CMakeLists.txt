cmake_minimum_required(VERSION 3.10.2)

project(hlc_ts LANGUAGES C CXX VERSION 1.0.0)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set($ENV{CMAKE_BUILD_PARALLEL_LEVEL} 4)

# Compiler features
include(SetCompilerFeatures)
include(SetCompilerWarnings)
include(SetPlatformFeatures)
include(SystemInformation)

# external
find_package(OpenSSL REQUIRED)

include(CTest)
enable_testing()

# static library components
add_subdirectory("./modules")

# object library components
add_subdirectory("./DataType")
add_subdirectory("./Codecs")
# add_subdirectory("./Templates")
add_subdirectory("./PlatformInterface")
add_subdirectory("./SUTInterface")
add_subdirectory("./TestExecution")
add_subdirectory("./TestLogging")
add_subdirectory("./TestCase")
add_subdirectory("./TestManagement")

# application
add_subdirectory("./TestSuite")