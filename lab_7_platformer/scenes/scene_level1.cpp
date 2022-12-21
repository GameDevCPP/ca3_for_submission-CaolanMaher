#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_health_player.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <fstream>
#include "../../json/json.h"
using json = nlohmann::json;

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

json player_data;

void Level1Scene::Load() {
    // TESTING
    //std::ifstream f("../../res/data/player_data.json");
    //json data = json::parse(f);
    //cout << "DATA" << data["pi"] << data["happy"] << endl;
    // END OF TESTING

  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("../../res/level_1.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
    player = makeEntity();

    // get player data from json
    std::ifstream f("../../res/data/player_data.json");
    player_data = json::parse(f);

    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(Vector2f(10.f, 15.f));

    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));

    auto h = player->addComponent<HealthComponentPlayer>();

    // get player's health from json
    h->setHealth(player_data["max_health"]);

    //player_data["max_health"] = 500;
  }

  //cout << "Player Health: " << player->get_components<HealthComponentPlayer>()[0]->getHealth() << endl;

  //auto h = player->get_components<HealthComponentPlayer>()[0];
  //h->setHealth(h->getHealth() - 50);

  //cout << "Player Health: " << player->get_components<HealthComponentPlayer>()[0]->getHealth() << endl;

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

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

  if (ls::getTileAt(player->getPosition()) == ls::END) {

      player->get_components<HealthComponentPlayer>()[0]->setHealth(77);

      player_data["current_health"] = player->get_components<HealthComponentPlayer>()[0]->getHealth();

      // update players json data with current data
      std::ofstream o("../../res/data/player_data.json");

      o << std::setw(4) << player_data << std::endl;

    Engine::ChangeScene((Scene*)&level2);
  }
  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
