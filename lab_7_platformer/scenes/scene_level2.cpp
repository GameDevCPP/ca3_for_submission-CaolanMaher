#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_player_attack.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_health_player.h"
#include "../components/cmp_flying_enemy.h"
#include "../components/cmp_double_jump.h"
#include "../components/cmp_adv_ground_enemy.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <fstream>
#include "../../json/json.h"
using json = nlohmann::json;

using namespace std;
using namespace sf;

json player_data_2;

sf::Music music_2;

static vector<shared_ptr<Entity>> doubleJumps;
static vector<shared_ptr<Entity>> enemies;

static shared_ptr<Entity> player;
void Level2Scene::Load() {
  cout << "Scene 2 Load" << endl;
  ls::loadLevelFile("../../res/level_2.txt", 40.0f);
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  cout << "OFFSET" << ho << endl;
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
    // *********************************
    player = makeEntity();

    // get player data from json
    std::ifstream f("../../res/data/player_data.json");
      player_data_2 = json::parse(f);

    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    //auto s = player->addComponent<ShapeComponent>();
    //s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    //s->getShape().setFillColor(Color::Magenta);
    //s->getShape().setOrigin(Vector2f(10.f, 15.f));
    // *********************************
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
    player->addTag("player");
      player->addComponent<AttackComponentPlayer>();
    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));

    auto h = player->addComponent<HealthComponentPlayer>();

    // get player's health from json
    h->setHealth(player_data_2["max_health"]);

    cout << h->getHealth() << endl;
  }

    // add flying enemy or advanced ground enemy
    //cout << "LOADING FLYING ENEMY" << endl;
    {

        if(player_data_2["is_hard_mode"] == true) {
            cout << "LOADING FLYING ENEMY" << endl;
            for (int i = 0; i < ls::findTiles('f').size(); i++) {
                auto flyingEnemy = makeEntity();
                flyingEnemy->setPosition(ls::getTilePosition(ls::findTiles('f')[i]) +
                                         Vector2f(0, 7.5));
                // *********************************
                // Add HurtComponent
                flyingEnemy->addComponent<HurtComponent>();
                // Add ShapeComponent, Red 16.f Circle
                auto s = flyingEnemy->addComponent<ShapeComponent>();
                s->setShape<sf::CircleShape>(16.f);
                s->getShape().setOrigin(Vector2f(8.f, 8.f));
                s->getShape().setFillColor(Color::Red);
                // Add EnemyAIComponent
                //enemy->addComponent<EnemyAIComponent>();
                flyingEnemy->addComponent<FlyingEnemyComponent>();
                enemies.push_back(flyingEnemy);
            }
        }
        else {
            cout << "LOADING GROUND ENEMY" << endl;
            for (int i = 0; i < ls::findTiles('a').size(); i++) {
                auto advGroundEnemy = makeEntity();
                advGroundEnemy->setPosition(ls::getTilePosition(ls::findTiles('a')[i]) +
                                         Vector2f(0, 7.5));
                // *********************************
                //auto p = advGroundEnemy->addComponent<PhysicsComponent>(true, Vector2f(20.f, 20.f));
                //p->setRestitution(.4f);
                //p->setFriction(.0001f);
                //p->impulse(Vector2f(-3.f, 0));
                //p->setMass(1000000000.f);
                // Add HurtComponent
                advGroundEnemy->addComponent<HurtComponent>();
                // Add ShapeComponent, Red 16.f Circle
                auto s = advGroundEnemy->addComponent<ShapeComponent>();
                s->setShape<sf::CircleShape>(16.f);
                s->getShape().setOrigin(Vector2f(16.f, 0));
                s->getShape().setFillColor(Color::Red);
                // Add EnemyAIComponent
                //enemy->addComponent<EnemyAIComponent>();
                advGroundEnemy->addComponent<AdvGroundEnemyComponent>();
                enemies.push_back(advGroundEnemy);
            }
        }

        //for_each(v.begin(), v.end(), [](int i)
        //{
        //    std::cout << i << " ";
        //});
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

    enemies.push_back(enemy);
    // *********************************
  }

  // Create Turret
  {
      for(int i = 0; i < ls::findTiles('t').size(); i++) {
          auto turret = makeEntity();
          turret->setPosition(ls::getTilePosition(ls::findTiles('t')[i]) +
                              Vector2f(20, 0));
          auto s = turret->addComponent<ShapeComponent>();
          s->setShape<sf::CircleShape>(16.f, 3);
          s->getShape().setFillColor(Color::Red);
          s->getShape().setOrigin(Vector2f(16.f, 16.f));
          turret->addComponent<EnemyTurretComponent>();

          enemies.push_back(turret);
      }
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

    music_2.openFromFile("../../res/audio/music/background_music.wav");
    music_2.play();
    music_2.setVolume(30.f);
    music_2.setLoop(true);

  cout << " Scene 2 Load Done" << endl;
  setLoaded(true);
}

void Level2Scene::UnLoad() {
  cout << "Scene 2 UnLoad" << endl;
  music_2.stop();
  player.reset();
    for(int i = 0; i < doubleJumps.size(); i++) {
        doubleJumps[i].reset();
    }
    doubleJumps.clear();
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i].reset();
    }
    enemies.clear();
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

  if(player->get_components<AttackComponentPlayer>()[0]->_isAttacking) {
      for (int i = 0; i < enemies.size(); i++) {
          auto enemy = enemies[i];

          if (pp.x < enemy->getPosition().x + 30
              && pp.x > enemy->getPosition().x - 30
              && pp.y > enemy->getPosition().y - 30
              && pp.y < enemy->getPosition().y + 30)
              {
              //cout << pp.y << " " << enemy->getPosition().y << endl;
              cout << "HIT ENEMY" << endl;
              //ents.list.erase(ents.list.begin() + 1 + i);
              enemies.erase(enemies.begin() + i);
              enemy->setForDelete();
          }
      }
  }

  if (ls::getTileAt(pp) == ls::END) {
      player_data_2["current_health"] = player->get_components<HealthComponentPlayer>()[0]->getHealth();
      player_data_2["current_level"] = 3;

      // update players json data with current data
      std::ofstream o("../../res/data/player_data.json");

      o << std::setw(4) << player_data_2 << std::endl;

    Engine::ChangeScene((Scene*)&level3);
      return;
  } else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level2);
      return;
  }
}

void Level2Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
