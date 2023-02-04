#pragma once

#include "component.h"
#include "SFML/Graphics.hpp"

class PositionComponent : public Component {
private:
    sf::Vector2<float> _pos;
public:
    explicit PositionComponent(const float &x = 0, const float &y = 0);

    explicit PositionComponent(const sf::Vector2<float> &vector2);

    void setPosition(const float &x, const float &y);

    void setPosition(sf::Vector2<float> &position);

    sf::Vector2<float> &getPosition();

    void cast() const override {};
};
