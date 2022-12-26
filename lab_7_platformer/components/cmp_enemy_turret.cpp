#include "cmp_enemy_turret.h"
#include "cmp_bullet.h"
#include "cmp_hurt_player.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <fstream>
#include "../../json/json.h"
//#include <SFML/Graphics.hpp>
using json = nlohmann::json;

using namespace std;
using namespace sf;

json turret_data;

void EnemyTurretComponent::update(double dt) {
  _firetime -= dt;
  if (_firetime <= 0.f) {
    fire();
    _firetime = 1.f;
  }
  static float angle = 0.f;
  angle += 1.f * dt;

  _parent->setRotation(180.f + sin(angle) * 45.f);
}

void EnemyTurretComponent::fire() const {

    for(int i = 0; i < _bullets.size(); i++) {
        auto bullet = _bullets[i];
        if (bullet->get_components<BulletComponent>()[0]->_isAvailable == 1) {
            bullet->setPosition(_parent->getPosition());
            auto p = bullet->get_components<PhysicsComponent>()[0];
            p->teleport(_parent->getPosition());
            p->impulse(sf::rotate(Vector2f(0, 15.f), -_parent->getRotation()));
            bullet->get_components<BulletComponent>()[0]->_isAvailable = false;
            break;
        }
    }
}

EnemyTurretComponent::EnemyTurretComponent(Entity* p)
    : Component(p)
    {
    // get turret data from json
    std::ifstream f("../../res/data/turret_data.json");
    turret_data = json::parse(f);

    _firetime = turret_data["firetime"];

    _bullets = vector<shared_ptr<Entity>>();
    cout << "CREATING BULLETS" << endl;
    for (int i = 0; i < turret_data["bullet_count"]; i++) {
        auto bullet = _parent->scene->makeEntity();
        bullet->addComponent<BulletComponent>();
        bullet->addComponent<HurtComponent>();
        auto s = bullet->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(8.f);
        s->getShape().setFillColor(Color::Red);
        s->getShape().setOrigin(Vector2f(8.f, 8.f));
        auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(8.f, 8.f));
        p->setRestitution(.4f);
        p->setFriction(.005f);
        _bullets.push_back(bullet);
    }
}
