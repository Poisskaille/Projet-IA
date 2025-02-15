#include "BTNode.hpp"

class AlerteRun : public BTNode {
private:
public:
    AlerteRun() {}
    NodeState execute() override {
        // Suivre le joueur

        // Passer la state en MENACE si les ennemis n'ont plus vu le joueur pendant 5secondes
        return NodeState::SUCCESS;
    }
};