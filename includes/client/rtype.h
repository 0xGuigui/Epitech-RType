#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include "client/resource_manager.h"
#include "client/keyboard_manager.h"
#include "client/world.h"

struct RType {
    explicit RType(const std::string &basePath) : textures(basePath + "/textures"), fonts(basePath + "/fonts"), sounds(basePath + "/sounds") {};

    RType(const RType &) = delete;

    RType &operator=(const RType &) = delete;

    RType(RType &&) = delete;

    RType &operator=(RType &&) = delete;

    ResourceManager<sf::Texture> textures;
    ResourceManager<sf::Font> fonts;
    ResourceManager<sf::SoundBuffer> sounds;
    KeyboardManager keyboard;
    World world;
};

void createMainPlayer();

extern RType rtype;
