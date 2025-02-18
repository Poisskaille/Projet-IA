#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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
};

#endif // PLAYER_HPP