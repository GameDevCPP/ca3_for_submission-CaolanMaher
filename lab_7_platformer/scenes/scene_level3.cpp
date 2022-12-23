#include "scene_level3.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_player_attack.h"
#include "../game.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_health_player.h"
#include <LevelSystem.h>
#include <iostream>
#include <fstream>
#include "../../json/json.h"
using json = nlohmann::json;

using namespace std;
using namespace sf;

json player_data_3;

sf::Music music_3;

static shared_ptr<Entity> player;

void Level3Scene::Load() {
  cout << "Scene 3 Load" << endl;
  ls::loadLevelFile("../../res/level_3.txt", 40.0f);
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
    // *********************************


    // pl->setPosition({100, 100});
      player = makeEntity();

      // get player data from json
      std::ifstream f("../../res/data/player_data.json");
      player_data_3 = json::parse(f);

      player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
      //auto s = player->addComponent<ShapeComponent>();
      //s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
      //s->getShape().setFillColor(Color::Magenta);
      //s->getShape().setOrigin(Vector2f(10.f, 15.f));

      auto sp = player->addComponent<SpriteComponent>();
      shared_ptr<sf::Texture> playerTexture;
      playerTexture = make_shared<sf::Texture>();
      cout << "TEXTURE 2" << endl;
      if(!playerTexture->loadFromFile("../../res/sprites/player_sheet.png", sf::IntRect({40, 40}, {50, 100}))) {
          cout << "ERROR" << endl;
      }
      sp->setTexure(playerTexture);
      sp->getSprite().setOrigin(Vector2f(25.f, 65.f));
      sp->getSprite().scale(Vector2f(0.4, 0.4));

      player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
      player->addTag("player");
      player->addComponent<AttackComponentPlayer>();

      auto h = player->addComponent<HealthComponentPlayer>();

      // get player's health from json
      h->setHealth(player_data_3["max_health"]);
    // *********************************
  }

  // Add physics colliders to level tiles.
  {
    // *********************************
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
    // *********************************
  }

    music_3.openFromFile("../../res/audio/music/background_music.wav");
    music_3.play();
    music_3.setVolume(music_3.getVolume() * 0.3);
    music_3.setLoop(true);

  cout << " Scene 3 Load Done" << endl;
  setLoaded(true);
}

void Level3Scene::UnLoad() {
  cout << "Scene 3 UnLoad" << endl;
  music_3.stop();
  player.reset();
  ls::unload();
  Scene::UnLoad();
}



void Level3Scene::Update(const double& dt) {

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
    Engine::ChangeScene((Scene*)&level4);
  } else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level3);
  }

  static float rocktime = 0.0f;
  rocktime -= dt;

  if (rocktime <= 0.f){
    rocktime  = 5.f;
    auto rock = makeEntity();
    rock->setPosition(ls::getTilePosition(ls::findTiles('r')[0]) +
                      Vector2f(0, 40) );
    rock->addComponent<BulletComponent>(30.f);
    auto s = rock->addComponent<ShapeComponent>();
    s->setShape<sf::CircleShape>(40.f);
    s->getShape().setFillColor(Color::Cyan);
    s->getShape().setOrigin(Vector2f(40.f, 40.f));
    auto p = rock->addComponent<PhysicsComponent>(true, Vector2f(75.f, 75.f));
    p->setRestitution(.4f);
    p->setFriction(.0001f);
    p->impulse(Vector2f(-3.f, 0));
    p->setMass(1000000000.f);
  }
  
}

void Level3Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
