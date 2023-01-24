#pragma once

#include "component.h"
#include "SFML/Graphics.hpp"

class PositionComponent : public Component {
private:
    sf::Vector2<float> _pos;
public:
    const sf::Vector2<float> &pos = _pos;

    explicit PositionComponent(const float &x = 0, const float &y = 0);

    void setX(const float &x);

    void setY(const float &y);

    void setPosition(const float &x = 0, const float &y = 0);

    void setPosition(sf::Vector2<float> &position);
};
