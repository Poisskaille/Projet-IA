#ifndef SHOOTER_ENEMY_HPP
#define SHOOTER_ENEMY_HPP
#include "GOAPPlanner.hpp"
#include "ShootAction.hpp"
#include "MoveToReloadAction.hpp"
#include "ReloadAction.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

class ShooterEnemy : public Enemy{
private:
    State state;
    GOAPPlanner planner;
    CircleShape shape;
    Vector2f position;

public:

    //void update(float deltaTime, Grid& grid, const Vector2f& playerPos) override{}

    void draw(RenderWindow& window) {
        window.draw(shape);
    }
};

#endif
