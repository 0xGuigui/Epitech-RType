#include "client/world.h"
#include "client/systems/render_system.h"
#include "client/components/render_component.h"
#include "client/components/position_component.h"
#include "client/components/scale_component.h"

void RenderSystem::update(sf::RenderWindow &window, World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<RenderComponent, PositionComponent>();

    for (const std::shared_ptr<Entity> &entity : entities) {
        std::shared_ptr<PositionComponent> position = entity->getComponent<PositionComponent>();
        std::shared_ptr<RenderComponent> render = entity->getComponent<RenderComponent>();
        std::shared_ptr<ScaleComponent> scale = entity->getComponent<ScaleComponent>();

        sf::Sprite &spr = render->getRender();
        if (scale)
            spr.setScale(scale->scale);
        spr.setPosition(position->pos);
    }
}

