#include "SFML/Graphics.hpp"
#include "client/rtype.h"
#include "client/entities/entities.h"
#include "client/components/components.h"
#include <iostream>

static const sf::Keyboard::Key directions[] {
    sf::Keyboard::Up,
    sf::Keyboard::Down,
    sf::Keyboard::Left,
    sf::Keyboard::Right
};

static const sf::Vector2<float> velocity[] {
        {0, -200},
        {0, 200},
        {-200, 0},
        {200, 0}
};

void createMainPlayer() {
    std::shared_ptr<Player> player = rtype.world.createEntity<Player>();

    for (int i = 0; i < 4; i++) {
        rtype.keyboard.bind(directions[i], [player, i]() {
            const sf::Vector2<float> &velo = player->getComponent<VelocityComponent>()->getVelocity();
            player->getComponent<VelocityComponent>()->setVelocity(velo.x + velocity[i].x, velo.y + velocity[i].y);
        }, [player, i]() {
            const sf::Vector2<float> &velo = player->getComponent<VelocityComponent>()->getVelocity();
            player->getComponent<VelocityComponent>()->setVelocity(velo.x - velocity[i].x, velo.y - velocity[i].y);
        });
    }
    rtype.keyboard.bind(sf::Keyboard::Space, [player]() {
        std::shared_ptr<Projectile> projectile = rtype.world.createEntity<Projectile>(player);

        projectile->getComponent<PositionComponent>()->setPosition(player->getComponent<PositionComponent>()->getPosition());
    }, []() {});
}
