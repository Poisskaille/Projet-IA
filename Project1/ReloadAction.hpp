#ifndef RELOAD_ACTION_HPP
#define RELOAD_ACTION_HPP
#include "Action.hpp"

class ReloadAction : public Action {
public:
    bool canExecute(const State& state) override {
        return state.AmmoFind();
    }

    void execute(State& state) override {
        if (state.AmmoFind()) {
            state.Reload(5);
            state.SetEmpthy(false);
            state.ammoFind = false;
        }
        /*std::cout << "C'est ce qu'il me fallait. \n";*/
        std::cout << "[ReloadAction] Rechargement terminé.\n";
    }
};

#endif