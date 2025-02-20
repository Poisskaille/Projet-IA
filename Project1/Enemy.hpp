#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Grid;

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);
    void update(float deltaTime, Grid& grid,const Vector2f& playerPos) override;
};

#endif // ENEMY_HPP