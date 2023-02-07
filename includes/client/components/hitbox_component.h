#pragma once

#include "client/entities/entity.h"
#include "SFML/Graphics.hpp"
#include <typeindex>
#include <functional>

class HitboxComponent : public Component {
private:
    sf::FloatRect _hitbox;
    std::function<void(std::shared_ptr<Entity> &, const std::type_index &)> _onCollide;
    std::vector<std::type_index> _collidableWith;

    // This function is the second part of setCollidables, as it wasn't possible to only clear the vector on the first call
    template<typename Entity = ::Entity, typename... Args>
    void _setCollidables() {
        // If there's no arguments then everything is collidable
        if (_collidableWith.empty() && std::is_same<Entity, ::Entity>()) {
            _collidableWith.emplace_back(typeid(::Entity));
            return;
        } else if (std::is_same<Entity, ::Entity>())
            return;
        _collidableWith.emplace_back(typeid(Entity));
        _setCollidables<Args...>();
    };
public:
    HitboxComponent() = default;

    HitboxComponent(const sf::FloatRect &hb, std::function<void(std::shared_ptr<Entity> &, const std::type_index &)> function);

    HitboxComponent(const sf::Sprite &sprite, std::function<void(std::shared_ptr<Entity> &, const std::type_index &)> function);

    // This function takes all the Entity types you want your Entity to collide with in template arguments
    template<typename... Args>
    void setCollidables() {
        _collidableWith.clear();
        _setCollidables<Args...>();
    };

    void setHitbox(const sf::FloatRect &hb);

    void setHitbox(const sf::Sprite &sprite);

    sf::FloatRect &getHitbox();

    void setOnCollide(std::function<void(std::shared_ptr<Entity> &, const std::type_index &)> &collideFunction);

    std::vector<std::type_index> &getCollidables();

    void onCollide(std::shared_ptr<Entity> &entity, const std::type_index &index);

    void cast() const override {};
};
