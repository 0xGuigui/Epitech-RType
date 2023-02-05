#pragma once

#include "component.h"
#include "SFML/Graphics.hpp"

class ScaleComponent : public Component {
private:
    sf::Vector2<float> _scale;
public:
    explicit ScaleComponent(const float &x = 1, const float &y = 1);

    explicit ScaleComponent(const sf::Vector2<float> &vector2);

    void setScale(const float &x, const float &y);

    void setScale(sf::Vector2<float> &s);

    sf::Vector2<float> getScale();

    void cast() const override {};
};
