//
// Created by caola on 23/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_FLYING_ENEMY_H
#define GAMES_ENGINEERING_CMP_FLYING_ENEMY_H

#include "cmp_actor_movement.h"


class FlyingEnemyComponent : public ActorMovementComponent {
private:
    sf::Vector2f _direction;
    std::weak_ptr<Entity> _player;

public:
    void update(double dt) override;

    explicit FlyingEnemyComponent(Entity* p);

    FlyingEnemyComponent() = delete;
};


#endif //GAMES_ENGINEERING_CMP_FLYING_ENEMY_H
