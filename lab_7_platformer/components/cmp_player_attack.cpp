//
// Created by caola on 21/12/2022.
//

#include "cmp_player_attack.h"
#include "cmp_player_physics.h"
#include <engine.h>
#include <SFML/Window/Keyboard.hpp>
#include "system_renderer.h"
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include "../../json/json.h"
using json = nlohmann::json;

json player_res;
using namespace sf;

AttackComponentPlayer::AttackComponentPlayer(Entity *p) : Component(p), _player(_parent->scene->ents.find("player")[0]) {
    std::ifstream f("../../res/data/player_data.json");
    player_res = json::parse(f);
    slashBuffer.loadFromFile(player_res["attack_sound"]);
    slashSound.setBuffer(slashBuffer);

    swordTexture.loadFromFile(player_res["weapon_image"]);
    swordSprite.setTexture(swordTexture);
    swordSprite.scale({0.04, 0.04});
    swordSprite.setOrigin({25.f, 25.f});
}

void AttackComponentPlayer::play(sf::String track) {
    if(track == "slash") {
        slashSound.play();
    }
}

//bool scaleSet = false;

void AttackComponentPlayer::update(double dt) {
    if(Keyboard::isKeyPressed(Keyboard::Z) && !_isAttacking) {
        // attack
        _isAttacking = true;
        //swordSprite.setPosition({_player.lock()->getPosition().x + 10, _player.lock()->getPosition().y - 20});

        // play sound effect
        play("slash");
    }

    if(_isAttacking) {
        if (_player.lock()->get_components<PlayerPhysicsComponent>()[0]->_facingRight) {
            swordSprite.setPosition({_player.lock()->getPosition().x + 10, _player.lock()->getPosition().y - 20});
        }
        else {
            swordSprite.setPosition({_player.lock()->getPosition().x - 10, _player.lock()->getPosition().y - 20});
        }
    }

    //if(_isAttacking) {
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        //if(_isAttacking) {
            if (_player.lock()->get_components<PlayerPhysicsComponent>()[0]->_facingRight) {
                swordSprite.scale({1, 1});
                //swordSprite.setPosition({_player.lock()->getPosition().x + 10, _player.lock()->getPosition().y - 20});
            } else {
                swordSprite.scale({-1, 1});
                //swordSprite.setPosition({_player.lock()->getPosition().x + 10, _player.lock()->getPosition().y - 20});
            }
        //}
    }
    else if(Keyboard::isKeyPressed(Keyboard::Left)) {
        //if(_isAttacking) {
            if (_player.lock()->get_components<PlayerPhysicsComponent>()[0]->_facingRight) {
                swordSprite.scale({-1, 1});
                //swordSprite.setPosition({_player.lock()->getPosition().x - 10, _player.lock()->getPosition().y - 20});
            } else {
                swordSprite.scale({1, 1});
                //swordSprite.setPosition({_player.lock()->getPosition().x - 10, _player.lock()->getPosition().y - 20});
            }
        //}
    }
    //}

    _currentTime -= dt;
    if (_currentTime <= 0.f) {
        //cout << "BULLET AVAILABLE" << endl;
        _isAttacking = false;
        _currentTime = _attackTime;
        //_parent->setForDelete();
    }
}

void AttackComponentPlayer::render() {
    //Renderer::queue(swordSprite.getTexture());
    if(_isAttacking) {
        Renderer::getWindow().draw(swordSprite);
    }
}