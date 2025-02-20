#include "FootStep.hpp"

Footstep::Footstep(Vector2f spawnPos): s_state(stepState::UNDISCOVERED)
{
	m_shape.setPosition(spawnPos);
	m_shape.setRadius(5);
	m_shape.setFillColor(Color(237, 237, 237,100));
}

Footstep::~Footstep(){}

void Footstep::draw(RenderWindow& window){ window.draw(m_shape); }

bool Footstep::shouldDestroy()
{
	if (m_lifespan.getElapsedTime().asSeconds() >= 4) {
		return true;
	}
	return false;
}

void Footstep::setState(stepState value){ s_state = value; }

CircleShape Footstep::getShape() { return m_shape; }
Footstep::stepState Footstep::getState()const { return s_state; }