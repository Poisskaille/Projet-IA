#ifndef GOAPPLANNER_HPP
#define GOAPPLANNER_HPP
#include "ShootAction.hpp"
#include "MoveToReloadAction.hpp"
#include "ReloadAction.hpp"
#include <vector>
enum class Goal {
    Tirer,
    Recharcher,
    ChercherMunitions
};

class GOAPPlanner {
public:
    std::vector<Action*> Plan(const State& initialState, Goal goal) {
        std::vector<Action*> plan;

        if (goal == Goal::Tirer && initialState.Ammo() > 0) {
            plan.push_back(new ShootAction());
        }

        if (goal == Goal::Recharcher && initialState.AmmoFind()) {
            plan.push_back(new ReloadAction());
        }

        if (goal == Goal::ChercherMunitions && initialState.Empthy()) {
            plan.push_back(new MoveToReloadAction());
        }

        return plan;
    }


};

#endif