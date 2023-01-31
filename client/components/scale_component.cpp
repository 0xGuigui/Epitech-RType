#include "client/components/scale_component.h"

ScaleComponent::ScaleComponent(const float &x, const float &y) : Component() {
    _scale = {x, y};
}

ScaleComponent::ScaleComponent(const sf::Vector2<float> &vector2) {
    _scale = vector2;
}

void ScaleComponent::setScale(const float &x, const float &y) {
    _scale = {x, y};
}

void ScaleComponent::setScale(sf::Vector2<float> &s) {
    _scale = s;
}
