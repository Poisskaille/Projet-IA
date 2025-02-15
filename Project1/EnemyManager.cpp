#include "EnemyManager.hpp"

void EnemyManager::update(RenderWindow& window, float deltaTime, Grid& grid,const FloatRect& playerBounds)
{
	draw(window);
	if (checkCollision(playerBounds)) { cout << "Collision" << endl; }
	for (auto& enemy : m_mgs_enemies) {
		enemy->update(deltaTime,grid);
	}
}

void EnemyManager::draw(RenderWindow& window)
{	
	for (auto& enemy : m_mgs_enemies) {
		window.draw(enemy->shape);		
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

void EnemyManager::deleteAllEnemy()
{
	m_mgs_enemies.clear();
}
