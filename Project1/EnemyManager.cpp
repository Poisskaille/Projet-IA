#include "EnemyManager.hpp"

void EnemyManager::update(RenderWindow& window, float deltaTime, Grid& grid,const FloatRect& playerBounds, 
	const Vector2f playerPos,const float& playerSpeed, const FloatRect& stunzone, bool stun)
{
	draw(window);
	if (checkCollision(playerBounds)) { cout << "Collision" << endl; }
	if (checkSpotted(playerSpeed, playerBounds,playerPos)) { cout << "Player entendu / appercu" << endl; }
	if (checkStun(stunzone, stun)) { cout << "Ennemi stun" << endl; }
	for (auto& enemy : m_mgs_enemies) {
		enemy->update(deltaTime,grid,playerPos);
		enemy->rayCasting(grid, window);
	}
	if (checkFOV(playerBounds)) {
		for (auto& enemy : m_mgs_enemies) {
			if(enemy->getState() != 2)
			enemy->setAlerteState();
		}
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

void EnemyManager::setNormalState() {
	for (auto& enemy : m_mgs_enemies) {
		enemy->setNormalState();
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
		if (playerBounds.intersects(enemy->getFirstCasting().getGlobalBounds()) && enemy->getState() != 2) {
			return true;
		}
	}
	return false;
}

bool EnemyManager::checkSpotted(const float& playerSpeed, const FloatRect& playerBounds, const Vector2f& playerPos)
{
	for (auto& enemy : m_mgs_enemies) {
		if (enemy->getSoundDetection().getGlobalBounds().intersects(playerBounds) && playerSpeed > 200 && enemy->getState() != 1 && enemy->getState() != 2
			|| enemy->getSecondCasting().getGlobalBounds().intersects(playerBounds) && playerSpeed > 200 && enemy->getState()!= 1 && enemy->getState() != 2) {
			enemy->setTime(0.f);
			enemy->setMove(false);
			enemy->setSpottedState(playerPos);
			return true;
		}
	}
	return false;
}

bool EnemyManager::checkStun(const FloatRect& stunzone, bool stun)
{
	for (auto& enemy : m_mgs_enemies) {
		if (enemy->shape.getGlobalBounds().intersects(stunzone) && stun) {
			enemy->setStunnedState();
			return true;
		}
	}
	return false;
}
void EnemyManager::deleteAllEnemy(){ m_mgs_enemies.clear(); }
