#include "BTNode.hpp"

class ConditionNormalRun : public BTNode {
private:
    Blackboard& blackboard;
public:
    ConditionNormalRun(Blackboard& bb) : blackboard(bb) {}
    NodeState execute() override {
        // Condition : Etat basique si rien ne se passe
        return;
    }
};