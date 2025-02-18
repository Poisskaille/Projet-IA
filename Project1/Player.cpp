// player.cpp
#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "Grid.hpp"

Player::Player(float x, float y) : Entity(x, y, Color::Blue) {
    m_stunZone.setRadius(30);
    m_stunZone.setOrigin(20,20);
    m_stunZone.setPosition(shape.getPosition());
    m_stunZone.setFillColor(Color::Transparent);
}

void Player::update(float deltaTime, Grid& grid,const Vector2f& playerPos) {
    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Z)) movement.y -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::S)) movement.y += SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Q)) movement.x -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::D)) movement.x += SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::LShift)) { SPEED = 400.f; }
    else { SPEED = 200.f; }
    if (Mouse::isButtonPressed(Mouse::Left) && !isStuning) { isStuning = true; delay.restart(); }

    if (delay.getElapsedTime().asSeconds() > 0.5f) {
        isStuning = false;
    }

    Vector2f newPosition = shape.getPosition() + movement;
    FloatRect newBounds(newPosition, shape.getSize());

    m_stunZone.setPosition(shape.getPosition());

    // Vérifier les quatre coins du joueur
    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    if (isWalkable(newBounds.left, newBounds.top) &&
        isWalkable(newBounds.left + newBounds.width - 1, newBounds.top) &&
        isWalkable(newBounds.left, newBounds.top + newBounds.height - 1) &&
        isWalkable(newBounds.left + newBounds.width - 1, newBounds.top + newBounds.height - 1)) {
        shape.move(movement);
    }
}

CircleShape Player::getStunZone()
{
    return m_stunZone;
}

bool Player::getStun()
{
    return isStuning;
}
