#include "FootStepsManager.hpp"

void FootStepManager::draw(RenderWindow& window)
{ for (auto& fs : m_footstepvec) { fs->draw(window); } }

void FootStepManager::update()
{
	if (!m_footstepvec.empty() && m_footstepvec.front()->shouldDestroy()) {
		m_footstepvec.erase(m_footstepvec.begin());
	}
	checkSeen();
}

void FootStepManager::addFootStep(Vector2f spawnPos)
{ m_footstepvec.push_back(make_unique<Footstep>(spawnPos)); }

void FootStepManager::checkSeen() {
	for (auto& enemy : manager.getEnemies()) {
		for (auto& step : m_footstepvec) {
			if (enemy->getFirstCasting().getGlobalBounds().intersects(step->getShape().getGlobalBounds()) && step->getState() == Footstep::stepState::UNDISCOVERED) {
				int x = rand() % 50;
				if (x >= 10) { step->setState(Footstep::stepState::IGNORED); }
				else { step->setState(Footstep::stepState::SPOTTED); enemy->setMenacedState(); }
			}
		}
	}
}