#pragma once

#include "client/entities/entity.h"
#include "SFML/Graphics.hpp"

class Background : public Entity {
public:
    explicit Background(const sf::RenderWindow &window);

    void cast() const override {};
};
