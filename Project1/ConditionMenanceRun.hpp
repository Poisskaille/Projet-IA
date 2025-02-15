#include "BTNode.hpp"

class ConditionMenaceRun : public BTNode {
private:
    Blackboard& blackboard;
public:
    ConditionMenaceRun(Blackboard& bb) : blackboard(bb) {}
    NodeState execute() override {
        // Condition : Si le state est en Menace
        return;
    }
};