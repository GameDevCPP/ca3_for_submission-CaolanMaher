#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include <SFML/Audio.hpp>

class HurtComponent : public Component {
protected:
  void fire() const;
  std::weak_ptr<Entity> _player;
    bool _canBeAttacked = true;
    float _hurtCooldown = 3.f;
    float _currentTime;
    sf::SoundBuffer hurtBuffer;
    sf::Sound hurtSound;


public:
  void update(double dt) override;
  void render() override {}
  explicit HurtComponent(Entity* p);
  HurtComponent() = delete;
};
