//
// Created by caola on 21/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_ITEM_H
#define GAMES_ENGINEERING_CMP_ITEM_H


#include "ecm.h"

class ItemComponent : public Component {
private:
    [[maybe_unused]] int item_duration;
    int effect;
    std::weak_ptr<Entity> _player;
    //enum EFFECT {
    //    DOUBLE_JUMP,
    //    HEALTH,
    //    SHIELD
    //};

public:
    void update(double dt) override;
    void render() override {}
    explicit ItemComponent(Entity* p, int duration, int effect);
    ItemComponent() = delete;
};


#endif //GAMES_ENGINEERING_CMP_ITEM_H
