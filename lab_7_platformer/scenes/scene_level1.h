#pragma once

#include "engine.h"
#include <SFML/Audio.hpp>

class Level1Scene : public Scene {
public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;

private:
    //sf::SoundBuffer background_music_buffer;
    //sf::Music background_music;
};
