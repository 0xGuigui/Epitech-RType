#include "client/systems/monsterSpawn_system.h"
#include "client/components/components.h"
#include "client/components/position_component.h"
#include "client/entities/monster.h"
#include "client/rtype.h"

void monsterSpawnSystem::update(sf::RenderWindow &window, World &world, float delta) {
    _spawnRate = 100;
    _spawnPositionY = rand() % (window.getSize().y - 100) + 100;
    _spawnPositionX = window.getSize().x + rand() % 100;
    _monsterSpeedX = rand() % 100 + 100;
    _monsterSpeedY = rand() % 20 + 20;


    if (_spawnTimer <= 0) {
        _monsterType = rand() % 4;
        monsterType type = static_cast<monsterType>(_monsterType);

        std::shared_ptr<Monster> monster = world.createEntity<Monster>(type);
        monster->getComponent<PositionComponent>()->setPosition(_spawnPositionX, _spawnPositionY);
        monster->getComponent<HealthComponent>()->setHealth(100);
        monster->getComponent<HealthComponent>()->setDamage(100);
        monster->getComponent<VelocityComponent>()->setVelocity(-_monsterSpeedX, _monsterSpeedY);

        _spawnCount++;
        _spawnTimer = _spawnRate;
    } else {
        _spawnTimer--;
    }
}
