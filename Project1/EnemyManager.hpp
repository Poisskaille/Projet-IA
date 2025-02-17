#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include "PatrolMGS.hpp"
#include "ShooterEnemy.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Grid;

class EnemyManager {
public:
	void update(RenderWindow& window, float deltaTime, Grid& grid, const FloatRect& playerBounds, const Vector2f playerPos, const float& playerSpeed);
	void draw(RenderWindow& window);


	void createMGSPatrol(float posX, float posY, Vector2f p1, Vector2f p2, Vector2f p3);
	void createShooterEnemy(float posX, float posY, Grid& grid);
	void setMenacedState();
	void deleteAllEnemy();

	bool checkCollision(const FloatRect& playerBounds);
	bool checkFOV(const FloatRect& playerBounds);
	bool checkSpotted(const float& playerSpeed, const FloatRect& playerBounds, const Vector2f& playerPos);

private:
	vector<unique_ptr<PatrolMGS>> m_mgs_enemies;
	vector<unique_ptr<ShooterEnemy>> m_shooter_enemies;
};

#endif