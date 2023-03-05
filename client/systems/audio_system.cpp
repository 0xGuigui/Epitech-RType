#include "client/systems/audio_system.h"
#include "client/components/components.h"
#include "client/components/audio_component.h"
#include "client/rtype.h"

void audioSystem::update(sf::RenderWindow &window, World &world, float delta) {
    for (const std::shared_ptr<Entity> &entity : world.getEntities<AudioComponent>()) {
        entity->getComponent<AudioComponent>()->play();
    }
}
