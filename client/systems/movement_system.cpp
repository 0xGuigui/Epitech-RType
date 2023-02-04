#include "client/world.h"
#include "client/systems/movement_system.h"
#include "client/components/position_component.h"
#include "client/components/velocity_component.h"

void MovementSystem::update(sf::RenderWindow &window, World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<PositionComponent, VelocityComponent>();

    for (const std::shared_ptr<Entity>& entity : entities) {
        std::shared_ptr<PositionComponent> position = entity->getComponent<PositionComponent>();
        std::shared_ptr<VelocityComponent> velocity = entity->getComponent<VelocityComponent>();

        position->setPosition(
                position->getPosition().x + (velocity->getVelocity().x * delta),
                position->getPosition().y + (velocity->getVelocity().y * delta)
                );
    }
}
