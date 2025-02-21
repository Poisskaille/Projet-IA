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
        if (state.Ammo() > 0) {
            state.Shoot(1);
            std::cout << "Tir effectué. Munitions restantes : " << state.Ammo() << "\n";
        }
        if (state.Ammo() <= 0) {
            state.SetEmpthy(true);
            state.ammoFind = false;
            std::cout << "Plus de munitions, passage à l'état Empthy." << std::endl;
        }
    }
};

#endif
