//
// Created by caola on 21/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_PLAYER_ATTACK_H
#define GAMES_ENGINEERING_CMP_PLAYER_ATTACK_H

#include "ecm.h"
#include <SFML/Audio.hpp>

class AttackComponentPlayer : public Component {

private:
    sf::SoundBuffer slashBuffer;
    sf::Sound slashSound;

public:
    AttackComponentPlayer() = delete;

    explicit AttackComponentPlayer(Entity* p);

    void play(sf::String track);

    void update(double dt) override;
    void render() override;
};


#endif //GAMES_ENGINEERING_CMP_PLAYER_ATTACK_H
