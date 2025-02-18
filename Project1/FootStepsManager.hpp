#include "FootStep.hpp"
#include "EnemyManager.hpp"
#include <cstdlib>

extern EnemyManager manager;

class FootStepManager {
public:

	void draw(RenderWindow& window);
	void update();
	void addFootStep(Vector2f spawnPos);

	void checkSeen();

private:

	vector<unique_ptr<Footstep>> m_footstepvec;
};