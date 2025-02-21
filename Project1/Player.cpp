// player.cpp
#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "Grid.hpp"

Player::Player(float x, float y) : Entity(x, y) {
    m_stunZone.setRadius(30);
    m_stunZone.setOrigin(20,20);
    m_stunZone.setPosition(shape.getPosition());
    m_stunZone.setFillColor(Color::Transparent);
    shape.setFillColor(Color::Cyan);
}

void Player::update(float deltaTime, Grid& grid,const Vector2f& playerPos) {
    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Z)) { movement.y -= SPEED * deltaTime; if (stepDelay.getElapsedTime().asSeconds() > m_float_stepDelay) { stepmanager.addFootStep(shape.getPosition()); stepDelay.restart(); } }
    if (Keyboard::isKeyPressed(Keyboard::S)) { movement.y += SPEED * deltaTime; if (stepDelay.getElapsedTime().asSeconds() > m_float_stepDelay) { stepmanager.addFootStep(shape.getPosition()); stepDelay.restart(); }}
    if (Keyboard::isKeyPressed(Keyboard::Q)) { movement.x -= SPEED * deltaTime; if (stepDelay.getElapsedTime().asSeconds() > m_float_stepDelay) { stepmanager.addFootStep(shape.getPosition()); stepDelay.restart(); }}
    if (Keyboard::isKeyPressed(Keyboard::D)) { movement.x += SPEED * deltaTime; if (stepDelay.getElapsedTime().asSeconds() > m_float_stepDelay) { stepmanager.addFootStep(shape.getPosition()); stepDelay.restart(); }}
    if (Keyboard::isKeyPressed(Keyboard::LShift)) { SPEED = 250; m_float_stepDelay = 0.2f; }
    else if (Keyboard::isKeyPressed(Keyboard::LControl)) { SPEED = 50.f; m_float_stepDelay = 10.f; }
    else { SPEED = 125.f; m_float_stepDelay = 1.f; }
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

void Player::checkProjectileCollision(std::vector<ShooterEnemy::Projectile>& projectiles) const{
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if (shape.getGlobalBounds().intersects(it->shape.getGlobalBounds())) {
            std::cout << "Ouch (collision)" << std::endl;
            it = projectiles.erase(it);
        }
        else {
            ++it;
        }
    }
}

CircleShape Player::getStunZone(){ return m_stunZone; }

bool Player::getStun() { return isStuning; }
