#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_set>
#include <algorithm>
#include "SFML/System.hpp"
#include "client/entities/entity.h"
#include "client/systems/system.h"

class World {
private:
    std::vector<std::shared_ptr<Entity>> _entities;
    std::vector<std::shared_ptr<System>> _systems;
    sf::Clock _timer;
public:
    World() = default;
    ~World() = default;

    [[maybe_unused]] Entity &createEntity();

    void removeEntity(const Entity &entity);

    template<typename Component = ::Component, typename... Args>
    [[nodiscard]] std::vector<std::shared_ptr<Entity>> getEntities() const {

        if (std::is_same<Component, ::Component>())
            return _entities;

        std::vector<std::shared_ptr<Entity>> ent = _entities;

        std::erase_if(ent, [](const std::shared_ptr<Entity> &e) -> bool {
            return e->getComponent<Component>() == nullptr;
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
