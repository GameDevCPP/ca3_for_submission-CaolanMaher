#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
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
        "Platformer\nPress Space to Start");
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

    // get player data from json
    std::ifstream f("../../res/data/player_data.json");
    player_data_menu = json::parse(f);

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
      if(player_data_menu["current_level"] == 1) {
          Engine::ChangeScene(&level1);
      }
      else if(player_data_menu["current_level"] == 2) {
          Engine::ChangeScene(&level2);
      }
      else if(player_data_menu["current_level"] == 3) {
          Engine::ChangeScene(&level3);
      }
      else if(player_data_menu["current_level"] == 4) {
          Engine::ChangeScene(&level4);
      }
  }

  Scene::Update(dt);
}
