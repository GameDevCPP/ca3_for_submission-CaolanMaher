#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
Level4Scene level4;

int main() {
    cout << "STARTING" << endl;
  Engine::Start(1280, 720, "Platformer",&menu);
}