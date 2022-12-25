//
// Created by caola on 23/12/2022.
//

#include "sound.h"
#include <fstream>
#include "../json/json.h"
using json = nlohmann::json;

json audio_data;

sf::Music backgroundMusic;
sf::SoundBuffer slashBuffer;
sf::Sound slashSound;

void SoundSystem::loadAudioFiles() {
    // get audio data from json
    std::ifstream f("../../res/data/audio.json");
    audio_data = json::parse(f);

    backgroundMusic.openFromFile(audio_data["background_music"]);

    backgroundMusic.play();
    backgroundMusic.setLoop(true);
}

void SoundSystem::playAudio(const char* sound) {
    if(strcmp(sound, "slash") == 0) {
        slashSound.play();
    }
    if(strcmp(sound, "background") == 0) {
        backgroundMusic.play();
        backgroundMusic.setLoop(true);
    }
}

//SoundSystem::SoundSystem() {
//    loadAudioFiles();
//}
