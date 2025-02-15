#include "BTNode.hpp"

class ConditionSpottedRun : public BTNode {
private:
    Blackboard& blackboard;
public:
    ConditionSpottedRun(Blackboard& bb) : blackboard(bb) {}
    NodeState execute() override {
        // Condition : Si un ennemi a appercu le joueur
        return;
    }
};