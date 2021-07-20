# Try to find Crypt library and include path.
# Once done this will define
# sets the <PackageName>_FOUND variable
# CRYPT_FOUND
# CRYPT_INCLUDE_DIR
# CRYPT_LIBRARIES

#find dir with specific file
find_path(CRYPT_INCLUDE_DIR wincrypt.h)
if(MSVC)
  # find dir with specific lib
  find_library(CRYPT_LIBRARY crypt32.lib)
else()
  find_library(CRYPT_LIBRARY crypt32)
endif()

# Handle the REQUIRED argument and set CRYPT_FOUND
# include FindPackageHandleStandardArgs.cmake in cmake tool env
include(FindPackageHandleStandardArgs)
# find package from env path
find_package_handle_standard_args(Crypt DEFAULT_MSG CRYPT_LIBRARY CRYPT_INCLUDE_DIR)

# for cmakeGUI
mark_as_advanced(CRYPT_INCLUDE_DIR)
mark_as_advanced(CRYPT_LIBRARY)

if(Crypt_FOUND)
  message(STATUS "Found Crypt library")
  add_definitions(-DCRYPT_SUPPORT)
  set(CRYPT_LIBRARIES ${CRYPT_LIBRARY})
endif()
