if(NOT TARGET openv2g)

  # Module library
  file(GLOB_RECURSE LIB_SOURCE_FILES 
    "openv2g/src/appHandshake/*.c"
    "openv2g/src/codec/*.c"
    "openv2g/src/din/*.c"
    "openv2g/src/iso1/*.c"
    "openv2g/src/iso2/*.c"
    "openv2g/src/transport/*.c"
    "openv2g/src/xmldsig/*.c"
  )
  file(GLOB_RECURSE LIB_HEADER_FILES 
    "openv2g/include/appHandshake/*.h"
    "openv2g/include/codec/*.h"
    "openv2g/include/din/*.h"
    "openv2g/include/iso1/*.h"
    "openv2g/include/iso2/*.h"
    "openv2g/include/transport/*.h"
    "openv2g/include/xmldsig/*.h"
  )
  add_library(openv2g ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})
  target_compile_definitions(openv2g PRIVATE OPENV2G_STANDALONE OPENV2G_SEPARATE_COMPILATION)
  target_include_directories(openv2g PUBLIC 
    "openv2g/include/appHandshake" 
    "openv2g/include/codec" 
    "openv2g/include/din" 
    "openv2g/include/iso1" 
    "openv2g/include/iso2" 
    "openv2g/include/transport" 
    "openv2g/include/xmldsig" 
  )

  # Module folder
  set_target_properties(openv2g PROPERTIES FOLDER modules/openv2g LINKER_LANGUAGE C)

endif()
