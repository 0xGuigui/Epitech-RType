#include "client/components/position_component.h"

PositionComponent::PositionComponent(const float &x, const float &y) : Component() {
    _pos = {x, y};
}

void PositionComponent::setX(const float &x) {
    _pos.x = x;
}

void PositionComponent::setY(const float &y) {
    _pos.y = y;
}

void PositionComponent::setPosition(const float &x, const float &y) {
    _pos = {x, y};
}

void PositionComponent::setPosition(sf::Vector2<float> &position) {
    _pos = position;
}
