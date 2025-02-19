#include "EnemyManager.hpp"
#include "Grid.hpp"
#include "Player.hpp"


void EnemyManager::update(RenderWindow& window, float deltaTime, Grid& grid,const FloatRect& playerBounds,
	const Vector2f playerPos,const float& playerSpeed, const FloatRect& stunzone, bool stun)
{

	if (!m_soundInit) {
		InitializeSound();
	}

	draw(window);
	if (checkCollision(playerBounds)) {}
	if (checkSpotted(playerSpeed, playerBounds,playerPos)) {}
	if (checkStun(stunzone, stun)) {}
	for (auto& enemy : m_mgs_enemies) {
		enemy->update(deltaTime,grid,playerPos);
		enemy->rayCasting(grid, window);
	}

	for (auto& enemy : m_shooter_enemies) { enemy->update(deltaTime, grid, playerPos); }

	if (checkFOV(playerBounds)) {
		for (auto& enemy : m_mgs_enemies) {
			if (enemy->getState() != PatrolMGS::State::STUNNED){
				alert.play();
				enemy->setAlerteState();
			}			
		}
	}
}

void EnemyManager::draw(RenderWindow& window)
{	
	for (auto& enemy : m_mgs_enemies) {
		enemy->draw(window);
	}
	for (auto& enemy : m_shooter_enemies) {
		enemy->draw(window);
	}
}

void EnemyManager::createMGSPatrol(float posX, float posY, Vector2i p1, Vector2i p2, Vector2i p3)
{ m_mgs_enemies.push_back(make_unique<PatrolMGS>(posX, posY, p1, p2, p3)); }


void EnemyManager::createShooterEnemy(float posX, float posY, Grid& grid) 
{ m_shooter_enemies.push_back(make_unique<ShooterEnemy>(posX, posY, grid)); }

void EnemyManager::setMenacedState()
{ for (auto& enemy : m_mgs_enemies) { enemy->setMenacedState(); } }


void EnemyManager::setNormalState() 
{ for (auto& enemy : m_mgs_enemies) { enemy->setNormalState(); } }

void EnemyManager::deleteAllEnemy() {
	m_mgs_enemies.clear();
	m_shooter_enemies.clear();
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
		if (playerBounds.intersects(enemy->getFirstCasting().getGlobalBounds()) && enemy->getState() != PatrolMGS::State::STUNNED) {
			return true;
		}
	}
	return false;
}

bool EnemyManager::checkSpotted(const float& playerSpeed, const FloatRect& playerBounds, const Vector2f& playerPos)
{
	for (auto& enemy : m_mgs_enemies) {
		if (playerSpeed > 200 && enemy->getState() != PatrolMGS::State::ALERTE && enemy->getState() != PatrolMGS::State::STUNNED && (enemy->getSoundDetection().getGlobalBounds().intersects(playerBounds) ||
			enemy->getSecondCasting().getGlobalBounds().intersects(playerBounds))) {
			enemy->setTime(0.f);
			enemy->setMove(false);
			enemy->setSpottedState(playerPos);
			return true;
		}	
	}
	return false;
}

void EnemyManager::InitializeSound()
{
	alertplay.loadFromFile("../assets/MGSAlert.mp3");
	alert.setBuffer(alertplay);
	m_soundInit = true;
}

vector<ConvexShape> EnemyManager::getShape() const
{
	vector<ConvexShape> shapes;
	for (const auto& enemy : m_mgs_enemies) {
		shapes.push_back(enemy->getFirstCasting());
	}
	return shapes;
}

const vector<unique_ptr<PatrolMGS>>& EnemyManager::getEnemies() const{ return m_mgs_enemies; }

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

