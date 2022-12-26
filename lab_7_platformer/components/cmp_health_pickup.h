//
// Created by caola on 25/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_HEALTH_PICKUP_H
#define GAMES_ENGINEERING_CMP_HEALTH_PICKUP_H

#include "cmp_item.h"

class HealthPickupComponent : public ItemComponent {
private:
    std::weak_ptr<Entity> _player;

public:
    void update(double dt) override;

    explicit HealthPickupComponent(Entity* p);

    HealthPickupComponent() = delete;

    [[maybe_unused]] int amountOfHealthAdded = 50;
};


#endif //GAMES_ENGINEERING_CMP_HEALTH_PICKUP_H
