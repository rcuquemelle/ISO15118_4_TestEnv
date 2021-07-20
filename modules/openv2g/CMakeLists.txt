message(STATUS "RUN RUN RUN RUN RUN RUN")

cmake_minimum_required(VERSION 2.8.9)
project(openv2g C)
set(CMAKE_BUILD_TYPE Release)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE LIB_HEADER_FILES "include/codec/*.h")
file(GLOB_RECURSE SOURCES "src/codec/*.c")

#Bring the headers, such as Student.h into the project
include_directories(PUBLIC "include/codec")

#Generate the shared library from the sources
add_library(openv2g STATIC ${LIB_HEADER_FILES} ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS openv2g DESTINATION /usr/lib)