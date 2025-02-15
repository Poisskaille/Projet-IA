#include "PatrolMGS.hpp"

class EnemyManager {
public:
	void update(RenderWindow& window, float deltaTime, Grid& grid, const FloatRect& playerBounds);
	void draw(RenderWindow& window);
	void deleteAllEnemy();


	void createMGSPatrol(float posX, float posY);
	void setMenacedState();
	bool checkCollision(const FloatRect& playerBounds);

private:
	vector<shared_ptr<PatrolMGS>> m_mgs_enemies;
};