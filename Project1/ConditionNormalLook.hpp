#include "BTNode.hpp"

class ConditionNormalLook : public BTNode {
private:
    Blackboard& blackboard;
public:
    ConditionNormalLook(Blackboard& bb) : blackboard(bb) {}
    NodeState execute() override {
        // Condition : Si un ennemi a atteint un point
        return;
    }
};