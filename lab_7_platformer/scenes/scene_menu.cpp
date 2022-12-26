#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include "../lib_sound/sound.h"
#include <iostream>
#include <fstream>
#include "../../json/json.h"
using json = nlohmann::json;

using namespace std;
using namespace sf;

json player_data_menu;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Wizard Strike");

    auto difficultyTxt = makeEntity();
    auto tx = difficultyTxt->addComponent<TextComponent>(
            "Press E for Easy Mode | Press H for Hard Mode");
    difficultyTxt->setPosition(Vector2f(500, 500));

    auto saveTxt = makeEntity();
    auto stxt = saveTxt->addComponent<TextComponent>(
            "Press Space to start a new game | Press Enter to Load saved game");
    saveTxt->setPosition(Vector2f(0, 1000));
  }

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

    // get player data from json
    std::ifstream f("../../res/data/player_data.json");
    player_data_menu = json::parse(f);

    if(sf::Keyboard::isKeyPressed(Keyboard::E)) {
        //isHardMode = false;
        player_data_menu["is_hard_mode"] = false;

        // update players json data with current data
        std::ofstream o("../../res/data/player_data.json");

        o << std::setw(4) << player_data_menu << std::endl;
    }

    if(sf::Keyboard::isKeyPressed(Keyboard::H)) {
        //isHardMode = true;
        player_data_menu["is_hard_mode"] = true;

        // update players json data with current data
        std::ofstream o("../../res/data/player_data.json");

        o << std::setw(4) << player_data_menu << std::endl;
    }

    if(sf::Keyboard::isKeyPressed(Keyboard::Space)) {
        Engine::ChangeScene(&level1);
    }

  if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {

      int playerLevel = player_data_menu["current_level"];

      switch(playerLevel) {
          [[unlikely]] case 1: Engine::ChangeScene(&level1);
          [[likely]] case 2: Engine::ChangeScene(&level2);
          case 3: Engine::ChangeScene(&level3);
      }

      if(player_data_menu["current_level"] == 1) {
          Engine::ChangeScene(&level1);
      }
      else if(player_data_menu["current_level"] == 2) {
          Engine::ChangeScene(&level2);
      }
      else if(player_data_menu["current_level"] == 3) {
          Engine::ChangeScene(&level3);
      }
      /*
      else if(player_data_menu["current_level"] == 4) {
          Engine::ChangeScene(&level4);
      }
       */
  }

  Scene::Update(dt);
}
