cmake_minimum_required(VERSION 3.0.0)
project(r-type LANGUAGES CXX)

include_directories(includes)

set(SHARED_SRC lib/error.cpp lib/random.cpp)
set(SERVER_SRC server/main.cpp)
set(CLIENT_SRC client/main.cpp
        client/keyboard_manager.cpp
        client/world.cpp
        client/entities/entity.cpp
        client/identifiable.cpp
        client/components/position_component.cpp
        client/components/render_component.cpp
        client/components/rotation_component.cpp
        client/components/velocity_component.cpp
        client/components/scale_component.cpp
        client/systems/movement_system.cpp
        client/components/hitbox_component.cpp
        client/systems/render_system.cpp
        client/systems/hitbox_system.cpp
        client/components/health_component.cpp
        client/systems/health_system.cpp
        client/entities/player.cpp
        client/entities/projectile.cpp
        client/entities/monster.cpp client/entities/indestructibleObstacle.cpp client/entities/obstacle.cpp client/entities/powerup.cpp client/init.cpp client/systems/system.cpp client/utils/background.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(r-type_client ${CLIENT_SRC} ${SHARED_SRC})
add_executable(r-type_server ${SERVER_SRC} ${SHARED_SRC})

target_link_libraries(r-type_client PRIVATE sfml-graphics)
target_link_libraries(r-type_server PRIVATE sfml-graphics)

target_compile_features(r-type_client PRIVATE cxx_std_20)
target_compile_features(r-type_server PRIVATE cxx_std_20)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_client POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_client> $<TARGET_FILE_DIR:r-type_client> COMMAND_EXPAND_LISTS)
endif ()
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET r-type_server POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:r-type_server> $<TARGET_FILE_DIR:r-type_server> COMMAND_EXPAND_LISTS)
endif ()

install(TARGETS r-type_client r-type_server)
