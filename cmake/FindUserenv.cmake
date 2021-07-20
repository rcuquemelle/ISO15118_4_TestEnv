# Try to find Userenv library and include path.
# Once done this will define
#
# USERENV_FOUND
# USERENV_INCLUDE_DIR
# USERENV_LIBRARIES

find_path(USERENV_INCLUDE_DIR userenv.h)
if(MSVC)
  find_library(USERENV_LIBRARY userenv.lib)
else()
  find_library(USERENV_LIBRARY userenv)
endif()

# Handle the REQUIRED argument and set USERENV_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Userenv DEFAULT_MSG USERENV_LIBRARY USERENV_INCLUDE_DIR)

mark_as_advanced(USERENV_INCLUDE_DIR)
mark_as_advanced(USERENV_LIBRARY)

if(Userenv_FOUND)
  message(STATUS "Found Userenv library")
  add_definitions(-DUSERENV_SUPPORT)
  set(USERENV_LIBRARIES ${USERENV_LIBRARY})
endif()
