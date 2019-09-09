cmake_minimum_required(VERSION 3.4)
project(proctree)

set(CMAKE_CXX_STANDARD 17)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Own modules
find_package(OpenGL REQUIRED)
add_subdirectory(proctree)
add_subdirectory(happytree)

