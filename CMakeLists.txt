# If someone uses a lower version of CMake building this fails.
cmake_minimum_required (VERSION 3.5)

include(FindPkgConfig)

set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(VCPKG_TARGET_TRIPLET "x64-mingw-static")
set(VCPKG_HOST_TRIPLET "x64-mingw-static")

# C++ standard to use.
set(CXX_STANDARD 17)

#set module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Name of your project.
project(BasicGui CXX)
message("Generating project ${CMAKE_PROJECT_NAME} ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("modulepath: ${CMAKE_MODULE_PATH}")
# find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(pcanbasic REQUIRED) 
find_package(OpenGL)

file(GLOB_RECURSE SOURCE_FILES "source/*.cpp" "PCANModule/*.cpp")
add_executable(ECLA_PM "main.cpp" ${SOURCE_FILES})
# pkg_check_modules(DEPS REQUIRED sigc++-3.0)
# include_directories(${DEPS_INCLUDE_DIRS})
# target_link_libraries(yourprogram ${DEPS_LIBRARIES})
target_include_directories(ECLA_PM PRIVATE ${pcanbasic_INCLUDE_DIR})
if (imgui_FOUND)
  target_link_libraries(ECLA_PM ${OPENGL_gl_LIBRARY} pcanbasic::pcanbasic imgui::imgui glfw Threads::Threads ws2_32 -pthread)
else()
  message(FATAL_ERROR "imgui library not found.")
endif()

set(CMAKE_INSTALL_RPATH "$ORIGIN") # Sets the RPATH to search for DLLs in the same directory as the executable.
