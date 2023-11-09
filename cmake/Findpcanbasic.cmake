include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)
list(APPEND CMAKE_PREFIX_PATH "C:/src/vcpkg/packages")

find_path(pcanbasic_INCLUDE_DIR 
      NAMES "PCANBasic.h" 
      PATHS "${CMAKE_CURRENT_LIST_DIR}/../../../../src/vcpkg/packages/pcanbasic_x86-windows/include")

message("pcanbasic_INCLUDE_DIR: ${pcanbasic_INCLUDE_DIR}")
if(NOT pcanbasic_INCLUDE_DIR)
    message("pcanbasic_INCLUDE_DIR could not be found")
endif()

get_filename_component(_pcanbasic_installed_prefix "${pcanbasic_INCLUDE_DIR}" DIRECTORY)

if(NOT pcanbasic_LIBRARY)
message("not pcanbasic_LIBRARY")
  find_library(pcanbasic_LIBRARY_RELEASE NAMES "PCANBasic.lib" PATHS "${_pcanbasic_installed_prefix}/lib")
  # find_library(pcanbasic_LIBRARY_DEBUG NAMES "pcanbasic" PATHS "${_pcanbasic_installed_prefix}/debug/lib" NO_DEFAULT_PATH)
  select_library_configurations(pcanbasic)
endif()

find_package_handle_standard_args(pcanbasic
  REQUIRED_VARS
    pcanbasic_INCLUDE_DIR
    pcanbasic_LIBRARY
)
mark_as_advanced(pcanbasic_INCLUDE_DIR pcanbasic_LIBRARY)

if(pcanbasic_FOUND)
message("pcanbasic_FOUND jajajajajdsfffffffffffffffffffffffffffffffffffffffffffffffffffff")
message("pcanbasic_INCLUDE_DIR: ${pcanbasic_INCLUDE_DIR}")
message("pcanbasic_LIBRARIES: ${pcanbasic_LIBRARIES}")

  if(NOT TARGET pcanbasic::pcanbasic)
    add_library(pcanbasic::pcanbasic UNKNOWN IMPORTED)
    set_target_properties(pcanbasic::pcanbasic PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${pcanbasic_INCLUDE_DIR}"
      IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
      IMPORTED_LOCATION "${pcanbasic_LIBRARY}"
    )
    message("not lib")

    if(EXISTS "${pcanbasic_LIBRARY_RELEASE}")
      set_property(TARGET pcanbasic::pcanbasic APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
      set_target_properties(pcanbasic::pcanbasic PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
        IMPORTED_LOCATION_RELEASE "${pcanbasic_LIBRARY_RELEASE}"
      )
      message("release")
    endif()
    if(EXISTS "${pcanbasic_LIBRARY_DEBUG}")
      set_property(TARGET pcanbasic::pcanbasic APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
      set_target_properties(pcanbasic::pcanbasic PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
        IMPORTED_LOCATION_DEBUG "${pcanbasic_LIBRARY_DEBUG}"
      )
      message("debug")
    endif()
  endif()
endif()
