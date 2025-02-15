#include "PatrolMGS.hpp"

class EnemyManager {
public:
	void update(RenderWindow& window, float deltaTime, Grid& grid, const FloatRect& playerBounds);
	void draw(RenderWindow& window);
	void deleteAllEnemy();


	void createMGSPatrol(float posX, float posY, Vector2f p1, Vector2f p2, Vector2f p3);
	void setMenacedState();
	bool checkCollision(const FloatRect& playerBounds);

private:
	vector<unique_ptr<PatrolMGS>> m_mgs_enemies;
};