#include "GOAPPlanner.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

void GOAPPlanner::addAction(Action* action) {
    m_actions.push_back(action);
}

void GOAPPlanner::addGoal(Goal goal) {
    m_goals.push_back(goal);
}

Action* GOAPPlanner::getBestAction() {
    // Trier les objectifs par priorité décroissante (plus grande priorité en premier)
    sort(m_goals.begin(), m_goals.end(), [](Goal a, Goal b) {
        return a.getPriority() > b.getPriority();
        });

    // Vérifier les actions disponibles
    for (const auto& goal : m_goals) {
        for (auto& action : m_actions) {
            if (action->canExecute()) {
                cout << "Execute action: " << action->getName() << " pour: " << goal.getName() << std::endl;
                return action;
            }
        }
    }

    cout << "Pas d'action à faire" << std::endl;
    return nullptr;
}
