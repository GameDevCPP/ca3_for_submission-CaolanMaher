//
// Created by caola on 24/12/2022.
//

#include "cmp_adv_ground_enemy.h"
#include <engine.h>
#include <LevelSystem.h>

using namespace std;
using namespace sf;

void AdvGroundEnemyComponent::update(double dt) {

    auto playerXPos = _player.lock()->getPosition().x;
    auto enemyXPos = _parent->getPosition().x;
    auto enemyYPos = _parent->getPosition().y;

    // player is to left of enemy
    if(playerXPos < enemyXPos) {
        enemyXPos = enemyXPos - _speed * dt;
    }
    // player is to right of enemy
    if(playerXPos > enemyXPos) {
        enemyXPos = enemyXPos + _speed * dt;
    }

    if(validMove(Vector2f(enemyXPos, enemyYPos)) && LevelSystem::getTileAt(Vector2f(enemyXPos, enemyYPos + 40)) == LevelSystem::WALL) {
        _parent->setPosition({enemyXPos, enemyYPos});
    }

    ActorMovementComponent::update(dt);
}

AdvGroundEnemyComponent::AdvGroundEnemyComponent(Entity *p) : ActorMovementComponent(p), _player(_parent->scene->ents.find("player")[0]) {
    _speed = 75.0f;
}
