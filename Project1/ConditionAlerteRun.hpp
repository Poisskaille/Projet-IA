#include "BTNode.hpp"

class ConditionAlerteRun : public BTNode {
private:
    Blackboard& blackboard;
public:
    ConditionAlerteRun(Blackboard& bb) : blackboard(bb) {}
    NodeState execute() override {
        // Condition : Si le State des ennemis est en Alerte
        return;
    }
};