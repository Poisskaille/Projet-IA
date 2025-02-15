#include "PatrolMGS.hpp"

PatrolMGS::PatrolMGS(float x, float y, Vector2f p1, Vector2f p2, Vector2f p3)
	: Enemy(x, y), m_position(x, y), m_p1(p1), m_p2(p2), m_p3(p3), currentWaypoint(0)
{
	shape.setSize({ 20, 20 });
	shape.setFillColor(Color::Magenta);
	shape.setPosition(m_position);
}

PatrolMGS::~PatrolMGS()
{
}

void PatrolMGS::update(float deltaTime, Grid& grid)
{
	Patrol(deltaTime);
	if (!canMove) {time += deltaTime;}
}

void PatrolMGS::Patrol(float deltaTime) {
	Vector2f waypoints[3] = { m_p1, m_p2, m_p3 };
	Vector2f target = waypoints[currentWaypoint];
	Vector2f direction = target - m_position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance < 5.0f) {
		canMove = false;
		if (time >= 2) { currentWaypoint = (currentWaypoint + 1) % 3; canMove = true; time = 0; }		
	}
	else {
		direction /= distance;
		m_position += direction * 2.0f;
	}

	if (canMove) {shape.setPosition(m_position);}
	
}

void PatrolMGS::setMenacedState()
{
	SPEED = 150.f;
	shape.setFillColor(Color::Yellow);
}

void PatrolMGS::setNormalState() {
	SPEED = 100.f;
	shape.setFillColor(Color::Green);
}

void PatrolMGS::setAlerteState() {
	SPEED = 200.f;
	shape.setFillColor(Color::Red);
}

void PatrolMGS::setSpottedState() {
	SPEED = 100.f;
	shape.setFillColor(Color(221, 235, 23));
}
