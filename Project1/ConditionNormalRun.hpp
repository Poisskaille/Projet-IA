#include "BTNode.hpp"

class ConditionNormalRun : public BTNode {
private:
    Blackboard& blackboard;
public:
    ConditionNormalRun(Blackboard& bb) : blackboard(bb) {}
    NodeState execute() override {
        if(blackboard.getState() == EnemyState::NORMAL){ return NodeState::SUCCESS; }       
        return NodeState::FAILURE;
    }
};