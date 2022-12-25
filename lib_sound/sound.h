//
// Created by caola on 23/12/2022.
//

#ifndef GAMES_ENGINEERING_SOUND_H
#define GAMES_ENGINEERING_SOUND_H

#include <SFML/Audio.hpp>

class SoundSystem {
private:
    static sf::Music backgroundMusic;

    static sf::SoundBuffer slashBuffer;
    static sf::Sound slashSound;

public:
    //SoundSystem();

    static void loadAudioFiles();

    static void playAudio(const char* sound);
};

#endif //GAMES_ENGINEERING_SOUND_H
