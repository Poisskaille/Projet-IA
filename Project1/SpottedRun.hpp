#include "BTNode.hpp"

class SpottedRun : public BTNode {
private:
public:
    SpottedRun() {}
    NodeState execute() override {
        // Va a la derni�re pos du joueur

        // Passe en NORMAL si rien a la fin
        return NodeState::SUCCESS;
    }
};