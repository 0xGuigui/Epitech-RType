#include "client/components/position_component.h"

PositionComponent::PositionComponent(const float &x, const float &y) {
    _pos = {x, y};
}

PositionComponent::PositionComponent(const sf::Vector2<float> &vector2) {
    _pos = vector2;
}

void PositionComponent::setPosition(const float &x, const float &y) {
    _pos = {x, y};
}

void PositionComponent::setPosition(sf::Vector2<float> &position) {
    _pos = position;
}

sf::Vector2<float> &PositionComponent::getPosition() {
    return _pos;
}
