#include "BTNode.hpp"

class ConditionSpottedRun : public BTNode {
private:
    Blackboard& blackboard;
    Player& p;
public:
    ConditionSpottedRun(Blackboard& bb, Player& pl) : blackboard(bb),p(pl) {}
    NodeState execute() override {
       /* if () {
            blackboard.setState(EnemyState::SPOTTED);
        }*/
        return;
    }
};