#include "client/systems/render_system.h"
#include "client/components/render_component.h"
#include "client/components/position_component.h"
#include "client/entities/entity.h"
#include "client/world.h"

void RenderSystem::update(World &world, float delta) {
    std::vector<std::shared_ptr<Entity>> entities = world.getEntities<RenderComponent, PositionComponent>();

    for (const std::shared_ptr<Entity> &entity : entities) {
        std::optional<std::shared_ptr<PositionComponent>> position = entity->getComponent<PositionComponent>();
        std::optional<std::shared_ptr<RenderComponent>> render = entity->getComponent<RenderComponent>();

        sf::Sprite &spr = render->get()->getRender();
        spr.setPosition(position->get()->pos);
    }
}
