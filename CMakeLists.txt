cmake_minimum_required(VERSION 3.10)
project(r-type)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Add the lib folder as a subdirectory
add_subdirectory(lib)

# Includes
include_directories(includes)

# Add the src/server directory as a target
add_executable(r-type_server src/server/main.cpp)

# Link the r-type_server target with the shared library
target_link_libraries(r-type_server PRIVATE shared)

# Add the src/client directory as a target
add_executable(r-type_client src/client/main.cpp)

# Link the r-type_client target with the shared library
target_link_libraries(r-type_client PRIVATE shared)
