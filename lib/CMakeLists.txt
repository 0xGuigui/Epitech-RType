cmake_minimum_required(VERSION 3.10)
project(shared)

# set output directory to build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# set static library output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Set the C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)

# Add the lib folder as a library
add_library(shared src/example.cpp ../includes/lib/lib.h)
