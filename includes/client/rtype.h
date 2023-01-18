#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>

// temporary includes to avoid "project not in project" errors
#include "client/resource_manager.h"
#include "client/keyboard_manager.h"
#include "client/ui/core.h"

struct RType {
    explicit RType(const std::string &basePath) : textures(basePath + "/textures"), fonts(basePath + "/fonts") {}

    RType(const RType &) = delete;

    RType &operator=(const RType &) = delete;

    RType(RType &&) = delete;

    RType &operator=(RType &&) = delete;

    ResourceManager<sf::Texture> textures;
    ResourceManager<sf::Font> fonts;
    KeyboardManager keyboard;
};

extern RType rtype;
