#include "State.hpp"
#include "GOAPPlanner.hpp"

class GOAPAgent {
private:
	State state;
	GOAPPlanner planner;
    sf::Clock actionClock;
    float actionCooldown = 1.0f;

public:
	GOAPAgent() {
		state.Shoot(5);
        state.SetEmpthy(false);
	}

    void PerformAction() {
        Goal goal;
        if (actionClock.getElapsedTime().asSeconds() < actionCooldown) {
            return; 
        }
        actionClock.restart(); 

        if (state.Empthy() && state.Ammo() == 0) {
            std::cout << "[GOAPAgent] État vide : recherche de munitions.\n";
            goal = Goal::ChercherMunitions;
        }
        else if (state.AmmoFind()) {
            std::cout << "[GOAPAgent] Munitions trouvées : rechargement en cours.\n";
            state.SetEmpthy(false);
            goal = Goal::Recharcher;
        }
        else if (state.Ammo() > 0) {
            std::cout << "[GOAPAgent] Munitions disponibles : prêt à tirer.\n";
            goal = Goal::Tirer;
        }
        else if (state.Ammo() <= 0) {
            state.SetEmpthy(true);
        }
        else {
            std::cout << "[GOAPAgent] Aucune condition remplie !\n";
            return;
        }

        std::vector<Action*> plan = planner.Plan(state, goal);

        for (auto action : plan) {
            if (action->canExecute(state)) {
                std::cout << "[GOAPAgent] Exécution de : " << typeid(*action).name() << "\n";
                action->execute(state);
            }
            else {
                std::cout << "[GOAPAgent] Action impossible : " << typeid(*action).name() << "\n";
            }
            delete action;
        }

        std::cout << "[GOAPAgent] État après action : Ammo = " << state.Ammo()
            << ", Empthy = " << state.Empthy()
            << ", AmmoFind = " << state.AmmoFind() << "\n";
    }

    

};