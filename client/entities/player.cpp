#include "client/entities/entities.h"
#include "client/components/components.h"
#include "client/rtype.h"

static const sf::Rect<int> playerColors[] = {
        {34, 3, 32, 13},
        {34, 20, 32, 13},
        {34, 37, 32, 13},
        {34, 54, 32, 13},
        {34, 71, 32, 13},
};

Player::Player(PlayerColor playerColor) : Entity() {
    sf::Sprite spr(rtype.textures.get("r-typesheet42"));
    spr.setTextureRect(playerColors[playerColor]);

    addComponent<PositionComponent>(500, 500);
    addComponent<VelocityComponent>(0, 0);
    addComponent<RenderComponent>(spr);
    addComponent<ScaleComponent>(3, 3);

    HealthComponent health(100, 0);
    health.setOnDeath([this]() {
        this->eraseSelf();
        std::cout << "You died" << std::endl;
    });
    addComponent<HealthComponent>(health);

    HitboxComponent hitboxComponent(spr, [this](std::shared_ptr<Entity> &e, const std::type_index &type) {
        std::shared_ptr<HealthComponent> healthComponent = e->getComponent<HealthComponent>();

        if (healthComponent) {
            std::shared_ptr<HealthComponent> thisHealth = getComponent<HealthComponent>();

            healthComponent->setHealth(healthComponent->getHealth() - thisHealth->getDamage());
        }
    });
    hitboxComponent.setCollidables<Projectile>();
    addComponent<HitboxComponent>(hitboxComponent);
}

void Player::setColor(PlayerColor playerColor) {
    std::shared_ptr<RenderComponent> renderComponent = getComponent<RenderComponent>();

    if (renderComponent)
        renderComponent->getRender().setTextureRect(playerColors[playerColor]);
}
