//
// Created by caola on 25/12/2022.
//

#include "cmp_health_pickup.h"

void HealthPickupComponent::update(double dt) {
    ItemComponent::update(dt);
}

HealthPickupComponent::HealthPickupComponent(Entity *p) : ItemComponent(p, 30, 1) {

}
