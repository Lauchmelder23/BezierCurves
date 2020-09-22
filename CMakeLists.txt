# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Bezier Curves")

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
if(NOT ${SDL2_FOUND})
	message(FATAL_ERROR "Could not locate SDL2. Aborting.")
endif()

# Include sub-projects.
add_subdirectory ("src")
