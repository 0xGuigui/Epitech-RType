#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_set>
#include <algorithm>
#include "SFML/System.hpp"
#include "client/entities/entity.h"
#include "client/systems/systems.h"

class World {
private:
    std::vector<std::shared_ptr<Entity>> _entities;
    std::vector<std::shared_ptr<System>> _systems = {
            std::make_shared<HealthSystem>(),
            std::make_shared<HitboxSystem>(),
            std::make_shared<MovementSystem>(),
            std::make_shared<RenderSystem>()
    };
    sf::Clock _timer;
public:
    World() = default;
    ~World() = default;

    template<typename Entity = ::Entity, typename... Args>
    std::shared_ptr<Entity> createEntity(Args&& ...args) {
        _entities.emplace_back(std::make_shared<Entity>(std::forward<Args>(args)...));

        return std::static_pointer_cast<Entity>(_entities.back());
    };

    void removeEntity(const Entity &entity);

    template<typename Type = ::Component, typename... Args>
    [[nodiscard]] std::vector<std::shared_ptr<Entity>> getEntities() const {

        if (std::is_same<Type, ::Component>() || std::is_same<Type, ::Entity>())
            return _entities;

        std::vector<std::shared_ptr<Entity>> ent = _entities;

        std::erase_if(ent, [](const std::shared_ptr<Entity> &e) -> bool {
            return e->getComponent<Type>() == nullptr && !dynamic_cast<Type *>(e.get());
        });

        std::vector<std::shared_ptr<Entity>> result = getEntities<Args...>();

        std::erase_if(result, [&ent](const std::shared_ptr<Entity> &e) -> bool {
            return std::count(ent.begin(), ent.end(), e) == 0;
        });
        return result;
    };

    void update(sf::RenderWindow &window);

    static std::string generateId();
};
