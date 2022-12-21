//
// Created by caola on 20/12/2022.
//

#ifndef GAMES_ENGINEERING_CMP_HEALTH_PLAYER_H
#define GAMES_ENGINEERING_CMP_HEALTH_PLAYER_H


#include "ecm.h"

class HealthComponentPlayer : public Component {
private:
    std::shared_ptr<int> _maxHealth;
    std::shared_ptr<int> _currentHealth;

public:
    HealthComponentPlayer() = delete;

    explicit HealthComponentPlayer(Entity* p);

    void update(double dt) override;
    void render() override;

    void setHealth(int newHealth);
    int getHealth();
};


#endif //GAMES_ENGINEERING_CMP_HEALTH_PLAYER_H
