#include "PatrolMGS.hpp"

class EnemyManager {
public:
	void update(RenderWindow& window, float deltaTime, Grid& grid, const FloatRect& playerBounds, const Vector2f playerPos, const float& playerSpeed, const FloatRect& stunzone, bool stun);
	void draw(RenderWindow& window);
	bool checkStun(const FloatRect& stunzone, bool stun);
	void deleteAllEnemy();


	void createMGSPatrol(float posX, float posY, Vector2i p1, Vector2i p2, Vector2i p3);
	void setMenacedState();

	void setNormalState();

	bool checkCollision(const FloatRect& playerBounds);
	bool checkFOV(const FloatRect& playerBounds);
	bool checkSpotted(const float& playerSpeed, const FloatRect& playerBounds, const Vector2f& playerPos);

private:
	vector<unique_ptr<PatrolMGS>> m_mgs_enemies;
};