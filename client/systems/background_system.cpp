#include "client/systems/background_system.h"
#include "client/entities/entities.h"
#include "client/components/components.h"
#include "client/utils/background.h"

void BackgroundSystem::update(sf::RenderWindow &window, World &world, float delta) {
    for (const std::shared_ptr<Entity>& bg_ptr : rtype.world.getEntities<Background>()) {
        std::shared_ptr<PositionComponent> component = bg_ptr->getComponent<PositionComponent>();

        if (component->getPosition().x <= -static_cast<float>(window.getSize().x))
            component->setPosition(static_cast<float>(window.getSize().x), 0);
    }
}
