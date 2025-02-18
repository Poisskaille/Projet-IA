#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Footstep {
public:
	enum class stepState{UNDISCOVERED,IGNORED,SPOTTED};

	Footstep(Vector2f spawnPos);
	~Footstep();

	void draw(RenderWindow& window);

	stepState getState()const;
	bool shouldDestroy();
	void setState(stepState value);

	CircleShape getShape();

private:

	Clock m_lifespan;
	CircleShape m_shape;
	stepState s_state;
};