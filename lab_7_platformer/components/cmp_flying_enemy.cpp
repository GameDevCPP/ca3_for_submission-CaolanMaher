//
// Created by caola on 23/12/2022.
//

#include "cmp_flying_enemy.h"
#include <engine.h>

void FlyingEnemyComponent::update(double dt) {

    auto playerXPos = _player.lock()->getPosition().x;
    auto playerYPos = _player.lock()->getPosition().y;
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
    // player is above enemy
    if(playerYPos < enemyYPos + 15) {
        enemyYPos = enemyYPos - _speed * dt;
    }
    // player is below enemy
    if(playerYPos > enemyYPos) {
        enemyYPos = enemyYPos + _speed * dt;
    }

    _parent->setPosition({enemyXPos, enemyYPos});

    ActorMovementComponent::update(dt);
}

FlyingEnemyComponent::FlyingEnemyComponent(Entity *p) : ActorMovementComponent(p), _player(_parent->scene->ents.find("player")[0]) {
    _speed = 50.0f;
}
