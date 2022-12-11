#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OQS::oqs" for configuration ""
set_property(TARGET OQS::oqs APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(OQS::oqs PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liboqs.a"
  )

list(APPEND _cmake_import_check_targets OQS::oqs )
list(APPEND _cmake_import_check_files_for_OQS::oqs "${_IMPORT_PREFIX}/lib/liboqs.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
