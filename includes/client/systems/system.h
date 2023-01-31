#pragma once
#include "SFML/Graphics.hpp"

class World;

class System {
public:
    virtual ~System() = default;
    virtual void update(sf::RenderWindow &window, World &world, float delta) = 0;
};
