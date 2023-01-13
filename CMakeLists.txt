cmake_minimum_required(VERSION 3.21)
project(r-type LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Add the lib folder as a subdirectory
add_subdirectory(lib)

# Includes
include_directories(includes)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Add the src/server directory as a target
add_executable(r-type_server src/server/main.cpp)

# Link the r-type_server target with the shared library and SFML
target_link_libraries(r-type_server PRIVATE shared sfml-graphics)
target_include_directories(r-type_server PRIVATE ${SFML_INCLUDE_DIR})

# Add the src/client directory as a target
add_executable(r-type_client src/client/main.cpp)

# Link the r-type_client target with the shared library and SFML
target_link_libraries(r-type_client PRIVATE shared sfml-graphics)
target_include_directories(r-type_client PRIVATE ${SFML_INCLUDE_DIR})

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_server POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_server> $<TARGET_FILE_DIR:r-type_server> COMMAND_EXPAND_LISTS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS r-type_server r-type_client)
