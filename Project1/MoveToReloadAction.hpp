#ifndef MOVE_TO_RELOAD_ACTION_HPP
#define MOVE_TO_RELOAD_ACTION_HPP
#include "Action.hpp"
#include "State.hpp"

class MoveToReloadAction : public Action {
public:
    bool canExecute(const State& state) override {
        return state.Empthy();
    }

    void execute(State& state) override {
        state.SetEmpthy(true); 
        std::cout << "[MoveToReloadAction] Zone atteinte, rechargement terminé.\n";
    }
};

#endif