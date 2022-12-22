#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class BulletComponent : public Component {
protected:
  float _lifetime;
  float _maxLifetime = 5.f;

public:
  void update(double dt) override;
  void render() override {}
  explicit BulletComponent(Entity* p, float lifetime = 5.f);
  BulletComponent() = delete;
    bool _isAvailable = true;
};
