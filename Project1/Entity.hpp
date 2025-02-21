#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Grid;

class Entity {
public:
    RectangleShape shape;
    Vector2f velocity;

    Entity(float x, float y);
    virtual void update(float deltaTime, Grid& grid, const Vector2f& playerPos) = 0;
};

#endif // ENTITY_HPP