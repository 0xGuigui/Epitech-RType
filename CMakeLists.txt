cmake_minimum_required(VERSION 3.0.0)

project(r-type LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(includes)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SHARED_SRC lib/example.cpp)
set(SERVER_SRC src/server/main.cpp)
set(CLIENT_SRC src/client/main.cpp)
set(PROJECT_LIBS sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

add_executable(r-type_server ${SERVER_SRC} ${SHARED_SRC})
add_executable(r-type_client ${CLIENT_SRC} ${SHARED_SRC})

target_link_libraries(r-type_server ${PROJECT_LIBS})
target_link_libraries(r-type_client ${PROJECT_LIBS})

target_include_directories(r-type_server PUBLIC ${SFML_INCLUDE_DIR})
target_include_directories(r-type_client PUBLIC ${SFML_INCLUDE_DIR})

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_server POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_server> $<TARGET_FILE_DIR:r-type_server> COMMAND_EXPAND_LISTS)
    add_custom_command(TARGET r-type_client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif ()

install(TARGETS r-type_server r-type_client)
