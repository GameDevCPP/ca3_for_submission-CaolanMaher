#include "cmp_hurt_player.h"
#include <engine.h>
#include "cmp_health_player.h"
#include "cmp_player_attack.h"
#include "../json/json.h"
#include <fstream>
using json = nlohmann::json;

using namespace std;
using namespace sf;

json player_audio;

void HurtComponent::update(double dt) {

    _currentTime -= dt;
    if (_currentTime <= 0.f && !_canBeAttacked) {
        std::cout << "Can Be Attacked" << std::endl;
        _canBeAttacked = true;
        _currentTime = _hurtCooldown;
        //_parent->setForDelete();
    }

  if (auto pl = _player.lock()) {
    if (length(pl->getPosition() - _parent->getPosition()) < 25.0 && _canBeAttacked
    && !pl->get_components<AttackComponentPlayer>()[0]->_isAttacking) {
        _canBeAttacked = false;
        _currentTime = _hurtCooldown;

        // play sound effect
        hurtSound.setVolume(50.f);
        hurtSound.play();

        cout << "PLAYER HIT" << endl;
        auto health = pl->get_components<HealthComponentPlayer>()[0]->getHealth();
        pl->get_components<HealthComponentPlayer>()[0]->setHealth(health - 25);

        cout << "HEALTH: " << pl->get_components<HealthComponentPlayer>()[0]->getHealth() << endl;

        if(pl->get_components<HealthComponentPlayer>()[0]->getHealth() <= 0) {
            pl->setForDelete();
            _parent->setForDelete();
            //cout << "ENEMY DELETED" << endl;
        }
    }
  }
}

HurtComponent::HurtComponent(Entity* p)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {

    // get player data from json
    std::ifstream f("../../res/data/player_data.json");
    player_audio = json::parse(f);

    if(hurtBuffer.loadFromFile(player_audio["hurt_sound"])) {
        hurtSound.setBuffer(hurtBuffer);
    }
}
