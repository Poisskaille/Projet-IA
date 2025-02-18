#ifndef SHOOTERENEMY_HPP
#define SHOOTERENEMY_HPP

#include "Enemy.hpp"
#include "GOAPPlanner.hpp"
#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Grid;

class ShooterEnemy : public Enemy {
public:
    ShooterEnemy(float x, float y, Grid& grid);
    void update(float deltaTime, Grid& grid) override;
    void draw(RenderWindow& window);

private:
    sf::Vector2f m_position;
    int m_ammo = 5;
    GOAPPlanner m_planner;
    Grid& m_grid;
};

#endif
