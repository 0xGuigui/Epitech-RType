#include "client/systems/monsterSpawn_system.h"
#include "client/components/components.h"
#include "client/components/position_component.h"
#include "client/entities/monster.h"
#include "client/rtype.h"

void monsterSpawnSystem::update(sf::RenderWindow &window, World &world, float delta) {
    _maxSpawn = rand() % 10 + 1;
    _spawnRate = rand() % 100 + 200;
    _spawnPositionY = rand() % (window.getSize().y - 100) + 100;
    _spawnPositionX = window.getSize().x + rand() % 100 + 120;
    _monsterSpeedX = rand() % 100 + 50;


    if (_spawnCount < _maxSpawn) {
        _monsterType = rand() % 4;
        auto type = static_cast<monsterType>(_monsterType);

        std::shared_ptr<Monster> monster = world.createEntity<Monster>(type);
        _monsterSpeedY = rand() % 50;
        if (rand() % 2 == 0)
            _monsterSpeedY = -_monsterSpeedY;
        monster->getComponent<PositionComponent>()->setPosition(_spawnPositionX, _spawnPositionY);
        monster->getComponent<HealthComponent>()->setHealth(100);
        monster->getComponent<HealthComponent>()->setDamage(100);
        monster->getComponent<VelocityComponent>()->setVelocity(-_monsterSpeedX, _monsterSpeedY);

        _spawnCount++;
        _spawnTimer = _spawnRate;
    } else if (_spawnTimer <= 0) {
        _spawnCount = 0;
    } else {
        _spawnTimer--;
    }
}
