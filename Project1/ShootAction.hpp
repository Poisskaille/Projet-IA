#ifndef SHOOT_ACTION_HPP
#define SHOOT_ACTION_HPP
#include "Action.hpp"
#include "State.hpp"

class ShootAction : public Action {
public:
    bool canExecute(const State& state) override {
        return state.Ammo() > 0;
    }

    void execute(State& state) override {
    }
};

#endif
