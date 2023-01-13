#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "resource_manager.h"

struct RType {
    explicit RType(const std::string &basePath) : textures(basePath + "/textures"), fonts(basePath + "/fonts") {}

    RType(const RType &) = delete;

    RType &operator=(const RType &) = delete;

    RType(RType &&) = delete;

    RType &operator=(RType &&) = delete;

    ResourceManager<sf::Texture> textures;
    ResourceManager<sf::Font> fonts;
};

extern RType rtype;
