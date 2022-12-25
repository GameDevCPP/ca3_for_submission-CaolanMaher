//
// Created by caola on 24/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_ADV_GROUND_ENEMY_H
#define GAMES_ENGINEERING_CMP_ADV_GROUND_ENEMY_H

#include "cmp_actor_movement.h"


class AdvGroundEnemyComponent : public ActorMovementComponent {
private:
    sf::Vector2f _direction;
    std::weak_ptr<Entity> _player;

public:
    void update(double dt) override;

    explicit AdvGroundEnemyComponent(Entity* p);

    AdvGroundEnemyComponent() = delete;
};


#endif //GAMES_ENGINEERING_CMP_ADV_GROUND_ENEMY_H
