#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "FootStepsManager.hpp"

extern FootStepManager stepmanager;

class Player : public Entity {
public:
    float SPEED = 200.0f;
    Player(float x, float y);
    void update(float deltaTime, Grid& grid, const Vector2f& playerPos) override;
    
    CircleShape getStunZone();
    bool getStun();

private:
    CircleShape m_stunZone;
    bool isStuning = false;

    Clock delay;
    Clock stepDelay;
    float m_float_stepDelay = 1.f;
};

#endif // PLAYER_HPP