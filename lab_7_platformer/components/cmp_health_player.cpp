//
// Created by caola on 20/12/2022.
//

#include "cmp_health_player.h"

HealthComponentPlayer::HealthComponentPlayer(Entity *p) : Component(p) {

}

void HealthComponentPlayer::update(double dt) {

}

void HealthComponentPlayer::render() {

}

void HealthComponentPlayer::setHealth(int newHealth) {
    std::shared_ptr<int> health;
    auto setHealth = std::make_shared<int>(newHealth);
    _currentHealth = setHealth;
}

int HealthComponentPlayer::getHealth() {
    return *_currentHealth;
}
