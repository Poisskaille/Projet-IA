#include "Enemy.hpp"

class PatrolMGS : public Enemy{
public:
	PatrolMGS(float x, float y, Vector2f p1, Vector2f p2, Vector2f p3);
	~PatrolMGS();

	void update(float deltaTime, Grid& grid) override;
	void draw(RenderWindow& window);

	void Patrol(float deltaTime);
	void Spotted(float deltaTime);

	void setMenacedState();
	void setNormalState();
	void setAlerteState();
	void setSpottedState(const Vector2f& playerPos);

	void rayCasting(Grid& grid,RenderWindow& window);

	ConvexShape getCasting();
	CircleShape getSoundDetection();

private:
	float SPEED = 100.0f;
	Vector2f m_position;

	int m_currentWaypoint;
	Vector2f m_p1, m_p2, m_p3;
	Vector2f m_playerPos;
	ConvexShape m_cone;
	bool m_canMove = true;

	Vector2f m_direction;
	CircleShape m_sounddetection;
	
	float m_time = 0;

	bool isNormal = true;
};  