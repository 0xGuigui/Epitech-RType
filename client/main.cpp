#include "SFML/Graphics.hpp"
#include "client/rtype.h"
#include "client/entities/entities.h"
#include "client/components/components.h"
#include "client/entities/powerup.h"

// Clion run version
//RType rtype("../resources");
// Terminal run version
// init global instance of RType
RType rtype("resources");

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "R-Type");
    window.setFramerateLimit(60);

//    std::shared_ptr<Player> player = rtype.world.createEntity<Player>();
//    std::shared_ptr<Projectile> projectile = rtype.world.createEntity<Projectile>();
//    std::shared_ptr<Projectile> projectile2 = rtype.world.createEntity<Projectile>();
//    projectile2->getComponent<VelocityComponent>()->setVelocity(-100, 0);
//    projectile2->getComponent<PositionComponent>()->setPosition(500, 500);
//      std::shared_ptr<PowerUp> powerUp = rtype.world.createEntity<PowerUp>();
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            rtype.keyboard.update(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        rtype.world.update(window);
        window.display();
    }
}
