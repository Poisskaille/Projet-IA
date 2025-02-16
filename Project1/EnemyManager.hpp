#include "PatrolMGS.hpp"

class EnemyManager {
public:
	void update(RenderWindow& window, float deltaTime, Grid& grid, const FloatRect& playerBounds, const Vector2f playerPos, const float& playerSpeed);
	void draw(RenderWindow& window);
	void deleteAllEnemy();


	void createMGSPatrol(float posX, float posY, Vector2f p1, Vector2f p2, Vector2f p3);
	void setMenacedState();
	bool checkCollision(const FloatRect& playerBounds);
	bool checkFOV(const FloatRect& playerBounds);
	bool checkSound(const float& playerSpeed, const FloatRect& playerBounds, const Vector2f& playerPos);

private:
	vector<unique_ptr<PatrolMGS>> m_mgs_enemies;
};