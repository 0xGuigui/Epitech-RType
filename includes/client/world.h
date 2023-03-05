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
    // Each time you create a system, add it here, each system is called in order so pay attention to that
    std::vector<std::shared_ptr<System>> _systems = {
            std::make_shared<BackgroundSystem>(),
            std::make_shared<AnimationSystem>(),
            std::make_shared<audioSystem>(),
            std::make_shared<HealthSystem>(),
            std::make_shared<HitboxSystem>(),
            std::make_shared<MovementSystem>(),
            std::make_shared<monsterSpawnSystem>(),
            std::make_shared<RenderSystem>(),
    };
    // timer clock to calculate delta time between systems update
    sf::Clock _timer;
public:
    World() = default;
    ~World() = default;

    // To call this function, give the type of the Entity in the template argument and the arguments needed to construct this class in the function arguments
    template<typename Entity = ::Entity, typename... Args>
    std::shared_ptr<Entity> createEntity(Args&& ...args) {
        /* Constructs a shared_ptr of the desired type in the back of the vector,
         * and pass on the args given in the function to the desired class's constructor
         */
        _entities.emplace_back(std::make_shared<Entity>(std::forward<Args>(args)...));

        return std::static_pointer_cast<Entity>(_entities.back());
    };

    void removeEntity(const Entity &entity);

    /* This function return the entities which match ALL template parameters given
     * You can pass on an Entity type or/and a Component type
     * For example if you call it like this: getEntities<Player>(), it will return
     * you all Player entities.
     * If you call it like this: getEntities<MovementComponent, VelocityComponent>(), it will return
     * you all Entities which have both MovementComponent AND VelocityComponent
     */
    template<typename Type = ::Component, typename... Args>
    [[nodiscard]] std::vector<std::shared_ptr<Entity>> getEntities() const {

        // Check if the recursive is complete or if it includes everything
        if (std::is_same<Type, ::Component>() || std::is_same<Type, ::Entity>())
            return _entities;

        std::vector<std::shared_ptr<Entity>> ent = _entities;

        /* Filters the entities by either:
         * Getting the component from the Entity to check if it exists
         * Trying to cast the Entity into the type given to check if it is of the same type
         */
        std::erase_if(ent, [](const std::shared_ptr<Entity> &e) -> bool {
            if (std::is_base_of<::Component, Type>())
                return e->getComponent<Type>() == nullptr;
            return !dynamic_cast<Type *>(e.get());
        });

        // Goes into the recursive to do it for each template argument
        std::vector<std::shared_ptr<Entity>> result = getEntities<Args...>();

        /* Filters the entities to only leave entities which are present in both vectors
         * It lets you check if they have everything that is asked
         */
        std::erase_if(result, [&ent](const std::shared_ptr<Entity> &e) -> bool {
            return std::count(ent.begin(), ent.end(), e) == 0;
        });
        return result;
    };

    void update(sf::RenderWindow &window);

    static std::string generateId();
};
