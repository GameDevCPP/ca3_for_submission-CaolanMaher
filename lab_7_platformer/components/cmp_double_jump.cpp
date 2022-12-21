//
// Created by caola on 21/12/2022.
//

#include "cmp_double_jump.h"

void DoubleJumpComponent::update(double dt) {
    ItemComponent::update(dt);
}

DoubleJumpComponent::DoubleJumpComponent(Entity *p) : ItemComponent(p, 30, 1) {
    //_parent
}

void DoubleJumpComponent::JumpUsed() {
    if(amountOfJumps > 0) {
        amountOfJumps -= 1;
    }
}
