#include "Enemy.hpp"

class PatrolMGS : public Enemy{
public:
	PatrolMGS(float x, float y);
	~PatrolMGS();

	void update(float deltaTime, Grid& grid) override;

	void setMenacedState();

	void setNormalState();

	void setAlerteState();

	void setSpottedState();


private:
	float SPEED = 100.0f;

	bool isMenaced = false;

	enum State{NORMAL,SPOTTED,ALERTE,MENACE};
	State state;
};  