#include "client/components/hitbox_component.h"

#include <utility>

HitboxComponent::HitboxComponent(const sf::FloatRect &hb, std::function<void()> function) {
    _hitbox = hb;
    _onCollide = std::move(function);
}

HitboxComponent::HitboxComponent(const sf::Sprite &sprite, std::function<void()> function) {
    _hitbox = sprite.getGlobalBounds();
    _onCollide = std::move(function);
}

void HitboxComponent::setHitbox(const sf::FloatRect &hb) {
    _hitbox = hb;
}

void HitboxComponent::setHitbox(const sf::Sprite &sprite) {
    _hitbox = sprite.getGlobalBounds();
}

void HitboxComponent::setOnCollide(std::function<void()> &collideFunction) {
    _onCollide = collideFunction;
}
