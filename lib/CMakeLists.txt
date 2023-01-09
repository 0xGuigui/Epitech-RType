cmake_minimum_required(VERSION 3.10)
project(shared)

# Set the C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)

# Add the lib folder as a library
add_library(shared src/example.cpp ../includes/lib/lib.h)
