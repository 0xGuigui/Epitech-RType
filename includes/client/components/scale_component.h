#pragma once

#include "component.h"
#include "SFML/Graphics.hpp"

class ScaleComponent : public Component {
private:
    sf::Vector2<float> _scale;
public:
    const sf::Vector2<float> &scale = _scale;

    explicit ScaleComponent(const float &x = 0, const float &y = 0);

    explicit ScaleComponent(const sf::Vector2<float> &vector2);

    void setScale(const float &x = 0, const float &y = 0);

    void setScale(sf::Vector2<float> &s);
};
