#include "Enemy.hpp"

class PatrolMGS : public Enemy{
public:
	PatrolMGS(float x, float y, Vector2f p1, Vector2f p2, Vector2f p3);
	~PatrolMGS();

	void update(float deltaTime, Grid& grid) override;

	void Patrol(float deltaTime);

	void setMenacedState();

	void setNormalState();

	void setAlerteState();

	void setSpottedState();


private:
	float SPEED = 100.0f;
	Vector2f m_position;

	int currentWaypoint;
	Vector2f m_p1, m_p2, m_p3;

	bool canMove = true;
	
	float time = 0;
};  