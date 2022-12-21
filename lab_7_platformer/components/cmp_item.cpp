//
// Created by caola on 21/12/2022.
//

#include "cmp_item.h"

void ItemComponent::update(double dt) {

}

ItemComponent::ItemComponent(Entity *p, int duration, int effect) : Component(p) {
    item_duration = duration;
    this->effect = effect;
}
