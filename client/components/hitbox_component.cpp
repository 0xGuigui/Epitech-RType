#include "client/components/hitbox_component.h"
#include <utility>

HitboxComponent::HitboxComponent(const sf::FloatRect &hb, std::function<void(std::shared_ptr<Entity> &)> function) {
    _hitbox = hb;
    _onCollide = std::move(function);
}

HitboxComponent::HitboxComponent(const sf::Sprite &sprite, std::function<void(std::shared_ptr<Entity> &)> function) {
    _hitbox = sprite.getGlobalBounds();
    _onCollide = std::move(function);
}

void HitboxComponent::setHitbox(const sf::FloatRect &hb) {
    _hitbox = hb;
}

void HitboxComponent::setHitbox(const sf::Sprite &sprite) {
    _hitbox = sprite.getGlobalBounds();
}

sf::FloatRect &HitboxComponent::getHitbox() {
    return _hitbox;
}

void HitboxComponent::setOnCollide(std::function<void(std::shared_ptr<Entity> &)> &collideFunction) {
    _onCollide = collideFunction;
}

std::vector<std::type_index> &HitboxComponent::getCollidables() {
    return _collidableWith;
}

void HitboxComponent::onCollide(std::shared_ptr<Entity> &entity) {
    _onCollide(entity);
}
