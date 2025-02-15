#include "BTNode.hpp"

class MenaceRun : public BTNode {
private:
public:
    MenaceRun() {}
    NodeState execute() override {
        // Joueur le comportement de Menace
        
        //Passe en Normal si Menace ne trouve rien pendant 5 secondes
        return NodeState::SUCCESS;
    }
};