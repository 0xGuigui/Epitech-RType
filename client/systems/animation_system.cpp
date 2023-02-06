#include "client/systems/animation_system.h"
#include "client/entities/entities.h"
#include "client/components/components.h"

void AnimationSystem::update(sf::RenderWindow &window, World &world, float delta) {
    for (const std::shared_ptr<Entity> &entity : world.getEntities<AnimationComponent>()) {
        entity->getComponent<AnimationComponent>()->animate(delta);
    }
}
