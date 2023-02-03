#pragma once

#include "client/entities/entity.h"
#include "SFML/Graphics.hpp"
#include <typeindex>
#include <functional>

class HitboxComponent : public Component {
private:
    sf::FloatRect _hitbox;
    std::function<void(std::shared_ptr<Entity> &)> _onCollide;
    std::vector<std::type_index> _collidableWith;

    template<typename Entity = ::Entity, typename... Args>
    void _setCollidables() {
        if (_collidableWith.empty() && std::is_same<Entity, ::Entity>()) {
            _collidableWith.emplace_back(typeid(::Entity));
            return;
        } else if (std::is_same<Entity, ::Entity>())
            return;
        _collidableWith.emplace_back(typeid(Entity));
        _setCollidables<Args...>();
    };
public:
    const sf::FloatRect &hitbox = _hitbox;
    const std::function<void(std::shared_ptr<Entity> &)> &onCollide = _onCollide;
    const std::vector<std::type_index> &collidableWith = _collidableWith;

    HitboxComponent() = default;

    HitboxComponent(const sf::FloatRect &hb, std::function<void(std::shared_ptr<Entity> &)> function);

    HitboxComponent(const sf::Sprite &sprite, std::function<void(std::shared_ptr<Entity> &)> function);

    template<typename... Args>
    void setCollidables() {
        _collidableWith.clear();
        _setCollidables<Args...>();
    };

    void setHitbox(const sf::FloatRect &hb);

    void setHitbox(const sf::Sprite &sprite);

    void setOnCollide(std::function<void(std::shared_ptr<Entity> &)> &collideFunction);

    void cast() const override {};
};
