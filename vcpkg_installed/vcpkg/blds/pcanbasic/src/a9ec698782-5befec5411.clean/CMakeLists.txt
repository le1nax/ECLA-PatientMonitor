cmake_minimum_required (VERSION 3.17)
project(medit-libs CXX)  

add_library(pcanbasic STATIC IMPORTED)
set_target_properties(pcanbasic PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/lib/PCANBasic.lib"
)

target_include_directories(pcanbasic INTERFACE "{CMAKE_CURRENT_LIST_DIR}/include")

include(GNUInstallDirs)

install(TARGETS pcanbasic
    EXPORT pcanbasic-targets
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)
install(EXPORT pcanbasic-targets
    FILE pcanbasic-targets.cmake
    NAMESPACE pcanbasic::
    DESTINATION lib/cmake/pcanbasic 
)
install(FILES pcanbasic.h
    DESTINATION include
)

