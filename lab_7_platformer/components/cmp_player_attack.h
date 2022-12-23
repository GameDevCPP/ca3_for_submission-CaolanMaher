//
// Created by caola on 21/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_PLAYER_ATTACK_H
#define GAMES_ENGINEERING_CMP_PLAYER_ATTACK_H

#include "ecm.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class AttackComponentPlayer : public Component {

private:
    sf::SoundBuffer slashBuffer;
    sf::Sound slashSound;
    std::weak_ptr<Entity> _player;
    bool _isAttacking = false;
    float _attackTime = 1.f;
    float _currentTime;
    sf::Texture swordTexture;
    sf::Sprite swordSprite;

public:
    AttackComponentPlayer() = delete;

    explicit AttackComponentPlayer(Entity* p);

    void play(sf::String track);

    void update(double dt) override;
    void render() override;
};


#endif //GAMES_ENGINEERING_CMP_PLAYER_ATTACK_H
