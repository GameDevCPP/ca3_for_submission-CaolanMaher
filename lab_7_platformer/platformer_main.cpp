#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include "../lib_image/image.h"
#include <LevelSystem.h>

using namespace std;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
Level4Scene level4;

int main() {
    cout << "STARTING" << endl;

    //TESTING
    //auto bmp_data = readBMP("../../res/levels/Untitled.bmp");
    //cout << to_string(bmp_data[0]) + to_string(bmp_data[1]) + to_string(bmp_data[2]) << endl;

    //ls::loadLevelFile("../../res/levels/newTest.bmp");


  Engine::Start(1280, 720, "Platformer",&menu);
}