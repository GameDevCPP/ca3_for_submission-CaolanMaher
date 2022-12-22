#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_health_player.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <fstream>
#include "../../json/json.h"
using json = nlohmann::json;

using namespace std;
using namespace sf;

json player_data_2;

static shared_ptr<Entity> player;
void Level2Scene::Load() {
  cout << "Scene 2 Load" << endl;
  ls::loadLevelFile("../../res/level_2.txt", 40.0f);
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
    // *********************************
    player = makeEntity();

    // get player data from json
    std::ifstream f("../../res/data/player_data.json");
      player_data_2 = json::parse(f);

    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(Vector2f(10.f, 15.f));
    // *********************************
    player->addTag("player");
    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));

    auto h = player->addComponent<HealthComponentPlayer>();

    // get player's health from json
    h->setHealth(player_data_2["max_health"]);
  }

  // Create Enemy
  {
    auto enemy = makeEntity();
    enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) +
                       Vector2f(0, 7.5));
    // *********************************
    // Add HurtComponent
    enemy->addComponent<HurtComponent>();
    // Add ShapeComponent, Red 16.f Circle
    auto s = enemy->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(16.f);
    s->getShape().setFillColor(Color::Red);
    // Add EnemyAIComponent
    enemy->addComponent<EnemyAIComponent>();
    // *********************************
  }

  // Create Turret
  {
    auto turret = makeEntity();
    turret->setPosition(ls::getTilePosition(ls::findTiles('t')[0]) +
                        Vector2f(20, 0));
    auto s = turret->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(16.f, 3);
    s->getShape().setFillColor(Color::Red);
    s->getShape().setOrigin(Vector2f(16.f, 16.f));
    turret->addComponent<EnemyTurretComponent>();
  }

  // Add physics colliders to level tiles.
    {
        auto walls = ls::findTiles(ls::WALL);
        for (auto w : walls) {
            auto pos = ls::getTilePosition(w);
            pos += Vector2f(20.f, 20.f); //offset to center
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
        }
    }

  cout << " Scene 2 Load Done" << endl;
  setLoaded(true);
}

void Level2Scene::UnLoad() {
  cout << "Scene 2 UnLoad" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {

    sf::FloatRect rect;
    rect.left = 300.f;
    rect.top = 900.f;
    rect.width = 1500.f;
    rect.height = 1000.f;
    sf::View view(rect);

    view.setCenter(Vector2f(player->getPosition().x, player->getPosition().y));

    // center camera on player
    Engine::GetWindow().setView(view);

  Scene::Update(dt);
  const auto pp = player->getPosition();
  if (ls::getTileAt(pp) == ls::END) {
      player_data_2["current_health"] = player->get_components<HealthComponentPlayer>()[0]->getHealth();
      player_data_2["current_level"] = 3;

      // update players json data with current data
      std::ofstream o("../../res/data/player_data.json");

      o << std::setw(4) << player_data_2 << std::endl;

    Engine::ChangeScene((Scene*)&level3);
  } else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level2);
  }
}

void Level2Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
