//
// Created by caola on 21/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_DOUBLE_JUMP_H
#define GAMES_ENGINEERING_CMP_DOUBLE_JUMP_H

#include "cmp_item.h"


class DoubleJumpComponent : public ItemComponent {
private:
    int amountOfJumps;
    std::weak_ptr<Entity> _player;

public:
    void update(double dt) override;

    void JumpUsed();

    explicit DoubleJumpComponent(Entity* p);

    DoubleJumpComponent() = delete;
};


#endif //GAMES_ENGINEERING_CMP_DOUBLE_JUMP_H
