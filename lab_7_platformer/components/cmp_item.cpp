//
// Created by caola on 21/12/2022.
//

#include "cmp_item.h"
#include <engine.h>

void ItemComponent::update(double dt) {
    //std::cout << "ITEM" << std::endl;
    if (auto pl = _player.lock()) {
        std::cout << pl->getPosition() << " " << _parent->getPosition() << std::endl;
        if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
            //pl->setForDelete();
            //_parent->setForDelete();
            std::cout << "PLAYER TOUCHED ITEM" << std::endl;
        }
    }
}

ItemComponent::ItemComponent(Entity *p, int duration, int effect) : Component(p)
//, _player(_parent->scene->ents.find("player")[0])
{
    item_duration = duration;
    this->effect = effect;
}
