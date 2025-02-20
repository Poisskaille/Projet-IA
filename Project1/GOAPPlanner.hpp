#ifndef GOAPPLANNER_HPP
#define GOAPPLANNER_HPP
#include "Action.hpp"
#include <vector>

class GOAPPlanner {
private:
    std::vector<Action*> actions;

public:
    void addAction(Action* action) { actions.push_back(action); }

    void planAndExecute(State& state) {
        for (auto* action : actions) {
            if (action->canExecute(state)) {
                action->execute(state);
                break;
            }
        }
    }
};

#endif