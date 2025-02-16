#ifndef GOAP_PLANNER_HPP
#define GOAP_PLANNER_HPP

#include "Action.hpp"
#include "Goal.hpp"
#include <vector>
using namespace std;

class GOAPPlanner {
public:
    void addAction(Action* action);
    void addGoal(Goal goal);
    Action* getBestAction();

private:
    vector<Action*> m_actions;
    vector<Goal> m_goals;
};

#endif
