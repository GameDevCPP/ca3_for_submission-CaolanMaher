#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_health_player.h"
#include "../components/cmp_player_attack.h"
#include "../components/cmp_double_jump.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <SFML/Audio.hpp>
#include <fstream>
#include "../../json/json.h"
#include <SFML/Graphics.hpp>
using json = nlohmann::json;

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static vector<shared_ptr<Entity>> doubleJumps;

json player_data;

sf::Music music;

void Level1Scene::Load() {

    // TESTING
    //std::ifstream f("../../res/data/player_data.json");
    //json data = json::parse(f);
    //cout << "DATA" << data["pi"] << data["happy"] << endl;
    // END OF TESTING

  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("../../res/level_1.txt", 40.0f);
    //ls::loadLevelFile("../../res/levels/newTest.bmp", 40.0f);

    cout << "LEVEL LOADED" << endl;

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  //background_music_buffer.loadFromFile("../../res/background_music.wav");
  //background_music.openFromFile("../../res/background_music.wav");

  //if(background_music_buffer.loadFromFile("../res/audio/music/background_music.wav")) {
      //background_music.setBuffer(background_music_buffer);
      //background_music.play();
  //}
  //else {
  //    throw std::runtime_error("Failed to load sound effect: ");
  //}

  // Create player
  {
    player = makeEntity();

    // get player data from json
    std::ifstream f("../../res/data/player_data.json");
    player_data = json::parse(f);

    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(0, -50));
      //player->setPosition(ls::getTilePosition(ls::findTiles(sf::Color(ls::START))[0]));
    //auto s = player->addComponent<ShapeComponent>();
    //s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    //s->getShape().setFillColor(Color::Magenta);
    //s->getShape().setOrigin(Vector2f(10.f, 15.f));

    cout << "TEXTURE" << endl;
    auto sp = player->addComponent<SpriteComponent>();
    shared_ptr<sf::Texture> playerTexture;
    playerTexture = make_shared<sf::Texture>();
      cout << "TEXTURE 2" << endl;
    if(!playerTexture->loadFromFile("../../res/sprites/player_sheet.png", sf::IntRect({40, 40}, {50, 100}))) {
        cout << "ERROR" << endl;
    }
    sp->setTexure(playerTexture);
    sp->getSprite().setOrigin(Vector2f(25.f, 25.f));
    sp->getSprite().scale(Vector2f(0.4, 0.4));
      cout << "Done TEXTURE" << endl;

    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
      player->addTag("player");
    player->addComponent<AttackComponentPlayer>();

    auto h = player->addComponent<HealthComponentPlayer>();

    //auto a = player->addComponent<AttackComponentPlayer>();

    //a->play("slash");

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

  // add double jump item
  cout << "LOADING DOUBLE JUMP" << endl;
    {
        for(int i = 0; i < ls::findTiles('d').size(); i++) {
            auto doubleJump = makeEntity();
            doubleJump->setPosition(ls::getTilePosition(ls::findTiles('d')[i]) + Vector2f(20, 20));
            cout << doubleJump->getPosition() << endl;
            //doubleJump->addComponent<DoubleJumpComponent>();
            auto s = doubleJump->addComponent<ShapeComponent>();
            s->setShape<sf::CircleShape>(10.f);
            s->getShape().setFillColor(Color::Yellow);
            s->getShape().setOrigin(Vector2f(10.f, 10.f));
            doubleJumps.push_back(doubleJump);
        }
    }

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  cout << " Scene 1 Load Done" << endl;

    music.openFromFile("../../res/audio/music/background_music.wav");
    music.play();
    music.setVolume(music.getVolume() * 0.3);
    music.setLoop(true);

  setLoaded(true);
}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  music.stop();
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

    sf::FloatRect rect;
    rect.left = 300.f;
    rect.top = 900.f;
    rect.width = 1500.f;
    rect.height = 1000.f;
    sf::View view(rect);

    view.setCenter(Vector2f(player->getPosition().x, player->getPosition().y));

    // center camera on player
    Engine::GetWindow().setView(view);

    //cout << player->getPosition() << endl;

    // check players position with double jump
    for(int i = 0; i < doubleJumps.size(); i++) {
        if (player->getPosition().x < doubleJumps[i]->getPosition().x + 5
            && player->getPosition().x > doubleJumps[i]->getPosition().x - 5
            && player->getPosition().y > doubleJumps[i]->getPosition().y - 5
            && player->getPosition().y < doubleJumps[i]->getPosition().y + 5
            && !player->get_components<PlayerPhysicsComponent>()[0]->_hasDoubleJump) {
            player->addComponent<DoubleJumpComponent>();
            player->get_components<PlayerPhysicsComponent>()[0]->_hasDoubleJump = true;
            cout << "DOUBLE JUMP GOT" << endl;
        }
    }

  if (ls::getTileAt(player->getPosition()) == ls::END) {

      //player->get_components<HealthComponentPlayer>()[0]->setHealth(77);

      player_data["current_health"] = player->get_components<HealthComponentPlayer>()[0]->getHealth();
      player_data["current_level"] = 2;

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
