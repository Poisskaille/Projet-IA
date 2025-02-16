#include "EnemyManager.hpp"

void EnemyManager::update(RenderWindow& window, float deltaTime, Grid& grid,const FloatRect& playerBounds, const Vector2f playerPos,const float& playerSpeed)
{
	draw(window);
	if (checkCollision(playerBounds)) { cout << "Collision" << endl; }
	if (checkFOV(playerBounds)) { cout << "Player vu" << endl; }
	if (checkSound(playerSpeed, playerBounds,playerPos)) { cout << "Player entendu" << endl; }
	for (auto& enemy : m_mgs_enemies) {
		enemy->update(deltaTime,grid);
		enemy->rayCasting(grid, window);
	}
}

void EnemyManager::draw(RenderWindow& window)
{	
	for (auto& enemy : m_mgs_enemies) {
		enemy->draw(window);
	}
}

void EnemyManager::createMGSPatrol(float posX, float posY, Vector2f p1, Vector2f p2, Vector2f p3)
{
	m_mgs_enemies.push_back(make_unique<PatrolMGS>(posX, posY,p1,p2,p3));
}

void EnemyManager::setMenacedState()
{
	for (auto& enemy : m_mgs_enemies) {
		enemy->setMenacedState();
	}
}

bool EnemyManager::checkCollision(const FloatRect& playerBounds)
{
	for (auto& enemy : m_mgs_enemies) {
		if (playerBounds.intersects(enemy->shape.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

bool EnemyManager::checkFOV(const FloatRect& playerBounds)
{
	for (auto& enemy : m_mgs_enemies) {
		if (playerBounds.intersects(enemy->getCasting().getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

bool EnemyManager::checkSound(const float& playerSpeed, const FloatRect& playerBounds, const Vector2f& playerPos)
{
	for (auto& enemy : m_mgs_enemies) {
		if (enemy->getSoundDetection().getGlobalBounds().intersects(playerBounds) && playerSpeed > 200) {
			enemy->setSpottedState(playerPos);
			return true;
		}
	}
	return false;
}

void EnemyManager::deleteAllEnemy()
{
	m_mgs_enemies.clear();
}
