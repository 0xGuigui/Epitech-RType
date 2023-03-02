#include "client/systems/health_system.h"
#include "client/entities/entity.h"
#include "client/components/health_component.h"
#include "client/world.h"
#include <vector>
#include <memory>

void HealthSystem::update(sf::RenderWindow &window, World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<HealthComponent>();

    for (std::shared_ptr<Entity> &entity : entities) {
        std::shared_ptr<HealthComponent> healthComponent = entity->getComponent<HealthComponent>();

        if (healthComponent->getHealth() <= 0)
            healthComponent->onDeath();
    }
}
