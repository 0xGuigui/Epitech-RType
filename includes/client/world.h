#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_set>
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
    std::vector<std::shared_ptr<Entity>> getEntities();

    void update();

    static std::string generateId();
};
