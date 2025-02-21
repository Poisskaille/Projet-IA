#ifndef RELOAD_ACTION_HPP
#define RELOAD_ACTION_HPP
#include "Action.hpp"

class ReloadAction : public Action {
public:
    bool canExecute(const State& state) override {
        return state.AmmoFind();
    }

    void execute(State& state) override {
        state.SetAmmoFind(true);
        std::cout << "[ReloadAction] Rechargement terminé.\n";
    }
};

#endif