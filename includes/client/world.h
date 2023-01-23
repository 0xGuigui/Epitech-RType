#pragma once

#include <vector>
#include <memory>
#include <string>

class Component;
class Entity;

class World {
private:
    std::vector<std::unique_ptr<Entity>> _entities;
public:
    [[maybe_unused]] const std::vector<std::unique_ptr<Entity>> &entities = _entities;

    World() = default;
    ~World() = default;

    [[maybe_unused]] Entity &createEntity();

    [[maybe_unused]] static std::string generateId();
};
