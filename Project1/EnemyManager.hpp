#ifndef ENEMYMANAGER_HPP
#define ENEMYMANAGER_HPP

#include "PatrolMGS.hpp"
#include "ShooterEnemy.hpp"
#include "TraperEnemy.hpp"
#include "SFML/Audio.hpp"

class Player;
class Grid;

class EnemyManager {
public:
	void update(RenderWindow& window, float deltaTime, Grid& grid, const FloatRect& playerBounds, const Vector2f playerPos, const float& playerSpeed, const FloatRect& stunzone, bool stun);
	void draw(RenderWindow& window);

	bool checkStun(const FloatRect& stunzone, bool stun);
	void deleteAllEnemy();


	void createMGSPatrol(float posX, float posY, Vector2i p1, Vector2i p2, Vector2i p3);
	void createShooterEnemy(float posX, float posY, Grid& grid);
	void createTraperEnemy(float posX, float posY, Grid& grid);
	void setMenacedState();

	void setNormalState();

	bool checkCollision(const FloatRect& playerBounds);
	bool checkFOV(const FloatRect& playerBounds);
	bool checkSpotted(const float& playerSpeed, const FloatRect& playerBounds, const Vector2f& playerPos);

	void InitializeSound();

	vector<ConvexShape> getShape()const;
	const vector<unique_ptr<PatrolMGS>>& getEnemies() const;

private:

	vector<unique_ptr<PatrolMGS>> m_mgs_enemies;
	vector<unique_ptr<ShooterEnemy>> m_shooter_enemies;
	vector<unique_ptr<TraperEnemy>> m_traper_enemies;

	SoundBuffer alertplay;
	Sound alert;

	bool m_soundInit = false;
};

#endif