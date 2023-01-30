#include "client/systems/movement_system.h"
#include "client/components/position_component.h"
#include "client/components/velocity_component.h"
#include "client/entities/entity.h"
#include "client/world.h"

void MovementSystem::update(World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<PositionComponent, VelocityComponent>();

    for (const std::shared_ptr<Entity>& entity : entities) {
        std::optional<std::shared_ptr<PositionComponent>> position = entity->getComponent<PositionComponent>();
        std::optional<std::shared_ptr<VelocityComponent>> velocity = entity->getComponent<VelocityComponent>();

        position->get()->setPosition(
                position->get()->pos.x + (position->get()->pos.x * velocity->get()->velocity.x),
                position->get()->pos.y + (position->get()->pos.y *velocity->get()->velocity.y)
                );
    }
}
