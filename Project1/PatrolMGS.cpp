#include "PatrolMGS.hpp"

PatrolMGS::PatrolMGS(float x, float y): Enemy(x, y), state(State::NORMAL)
{
	shape.setPosition(x, y);
	shape.setFillColor(Color::Magenta);
	shape.setSize({ 20,20 });
}

PatrolMGS::~PatrolMGS()
{
}

void PatrolMGS::update(float deltaTime, Grid& grid)
{
}

void PatrolMGS::setMenacedState()
{
	SPEED = 150.f;
	state = State::MENACE;
	shape.setFillColor(Color::Yellow);
}

void PatrolMGS::setNormalState() {
	SPEED = 100.f;
	state = State::NORMAL;
	shape.setFillColor(Color::Green);
}

void PatrolMGS::setAlerteState() {
	SPEED = 200.f;
	state = State::ALERTE;
	shape.setFillColor(Color::Red);
}

void PatrolMGS::setSpottedState() {
	SPEED = 100.f;
	state = State::SPOTTED;
	shape.setFillColor(Color(221, 235, 23));
}
