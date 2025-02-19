#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.hpp"

using namespace std;
using namespace sf;

class CameraMGS {
public:

	CameraMGS(Vector2f spawnPos, float minAngle, float maxAngle);
	~CameraMGS();

	void update(float deltaTime, Grid& grid);
	void Rotate(float deltaTime);
	void draw(RenderWindow& window);
	void rayCasting(Grid& grid);

private:

	RectangleShape m_shape;
	ConvexShape m_vision;

	float m_minAngle;
	float m_maxAngle;
	float m_currentAngle;

	bool m_reverseSwing = false;
};