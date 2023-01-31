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

template<typename Entity, typename ...Args>
void HitboxComponent::_setCollidables() {
    if (_collidableWith.empty() && std::is_same<Entity, ::Entity>()) {
        _collidableWith.emplace_back(typeid(::Entity));
        return;
    } else if (std::is_same<Entity, ::Entity>())
        return;
    _collidableWith.emplace_back(typeid(Entity));
    _setCollidables<Args...>();
}

template<typename ...Args>
void HitboxComponent::setCollidables() {
    _collidableWith.clear();
    _setCollidables<Args...>();
}

void HitboxComponent::setHitbox(const sf::FloatRect &hb) {
    _hitbox = hb;
}

void HitboxComponent::setHitbox(const sf::Sprite &sprite) {
    _hitbox = sprite.getGlobalBounds();
}

void HitboxComponent::setOnCollide(std::function<void(std::shared_ptr<Entity> &)> &collideFunction) {
    _onCollide = collideFunction;
}
