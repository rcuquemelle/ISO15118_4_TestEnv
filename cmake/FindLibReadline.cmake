# Try to find UUID library and include path.
# Once done this will define
#
# LIBREADLINE_FOUND
# LIBREADLINE_INCLUDE_DIR
# LIBREADLINE_LIBRARIES

find_path(LIBREADLINE_INCLUDE_DIR readline/readline.h)
find_library(LIBREADLINE_LIBRARY readline)

# Handle the REQUIRED argument and set LIBREADLINE_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBREADLINE DEFAULT_MSG LIBREADLINE_LIBRARY LIBREADLINE_INCLUDE_DIR)

mark_as_advanced(LIBREADLINE_INCLUDE_DIR)
mark_as_advanced(LIBREADLINE_LIBRARY)

if(LIBREADLINE_FOUND)
  message(STATUS "Found LIBREADLINE library")
  add_definitions(-DLIBREADLINE_SUPPORT)
  set(LIBREADLINE_LIBRARIES ${LIBREADLINE_LIBRARY})
endif()
