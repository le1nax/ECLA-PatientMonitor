# If someone uses a lower version of CMake building this fails.
cmake_minimum_required (VERSION 3.17)

# Name of your project.
project(BasicGui CXX)

#set module path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
list(APPEND CMAKE_PREFIX_PATH "C:/src/vcpkg/packages")

# set(pcanbasic_DIR "C:/src/vcpkg/ports/pcanbasic")

set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")
# list(APPEND CMAKE_MODULE_PATH "C:/lib_install")

# Project version (e.g. 1.0.0).
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# C++ standard to use.
set(CXX_STANDARD 17)
message("Generating project ${CMAKE_PROJECT_NAME} ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Find the required libs from your package manager (vcpkg).
# find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(pcanbasic REQUIRED) 

file(GLOB_RECURSE SOURCE_FILES "source/*.cpp" "PCANModule/*.cpp")
add_executable(
  ECLA_PM 
  "main.cpp"
  ${SOURCE_FILES}
 )

# set(pcanbasic_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../src/vcpkg/packages/pcanbasic_x86-windows")
# set(CMAKE_PREFIX_PATH 
#   "${pcanbasic_DIR}"
#     )

# find_path(pcanbasic_INCLUDE_DIR
#              NAMES "PCANBasic.h"
#              HINTS "${CMAKE_CURRENT_LIST_DIR}/PCANBasic/include")

# if(NOT pcanbasic_INCLUDE_DIR)
#     message("find_path didnt work")
# endif()

# message("pcanbasic_DIR: ${pcanbasic_DIR}")
# message("pcanbasic_INCLUDE_DIR: ${pcanbasic_INCLUDE_DIR}")

 #Include PCANBasic Lib
#  find_library(PCANBasic
#     NAMES PCANBasic.lib
#     PATHS "C:/src/vcpkg/packages/pcanbasic_x86-windows/lib"
# )

# find_path(PCANBasic_INCLUDE_DIR
#     NAMES PCANBasic.h
#     PATHS "C:/src/vcpkg/packages/pcanbasic_x86-windows/include"
# )

# include_directories(${PCANBasic_INCLUDE_DIR})
target_include_directories(ECLA_PM PRIVATE ${pcanbasic_INCLUDE_DIR})
# include_directories(${pcanbasic_INCLUDE_DIR})
# target_include_directories(ECLA_PM PRIVATE "C:/src/vcpkg/packages/pcanbasic_x86-windows/lib")
# link_directories("C:/src/vcpkg/packages/pcanbasic_x86-windows/lib")
# link_directories("C:/src/vcpkg/ports/pcanbasic/lib")
# link_directories(${pcanbasic_LIBRARIES})
# target_link_libraries(ECLA_PM PRIVATE pcanbasic)
# target_link_libraries(ECLA_PM PUBLIC ${PCANBasic})

# Copy the PCANBasic DLL to the output directory
# add_custom_command(TARGET ECLA_PM POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     "C:/src/vcpkg/packages/pcanbasic_x86-windows/bin/pcanbasic.dll"
#         $<TARGET_FILE_DIR:ECLA_PM>)
# configure_file("C:/src/vcpkg/packages/pcanbasic_x86-windows/bin/pcanbasic.dll" ${CMAKE_BINARY_DIR} COPYONLY)
target_link_libraries(ECLA_PM pcanbasic::pcanbasic glfw imgui::imgui Threads::Threads ws2_32 -pthread)
set(CMAKE_INSTALL_RPATH "$ORIGIN") # Sets the RPATH to search for DLLs in the same directory as the executable.


# Link the GUI libraries into the executable.
# target_link_libraries(ECLA_PM PUBLIC glfw imgui::imgui Threads::Threads ws2_32 -pthread)
#target_link_libraries(ECLA_PM PUBLIC glfw imgui::imgui Threads::Threads ws2_32 -lsocket -lnsl -pthread)

# Add the folder with 'gui_application.hpp' and 'gui_main.hpp' to the include path.
# This way we can '#include<gui_application.hpp>'.
target_include_directories(ECLA_PM PRIVATE "../lib")
target_include_directories(ECLA_PM PRIVATE ${ImGui_LIBRARIES})

# get_target_property(linked_libraries ECLA_PM LINK_LIBRARIES)

# foreach(lib ${linked_libraries})
#     get_target_property(lib_location ${lib} IMPORTED_LOCATION)

#     # Extract the directory from the full path using string manipulation
#     get_filename_component(lib_directory "${lib_location}" DIRECTORY)

#     message(STATUS "Directory of ${lib}: ${lib_directory}")
# endforeach()

