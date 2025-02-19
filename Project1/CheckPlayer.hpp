#include "BTNode.hpp"
#include "Blackboard.hpp"

class CheckForPlayer : public BTNode {
private:
    Blackboard& blackboard;
public:
    CheckForPlayer(Blackboard& bb) : blackboard(bb) {}

    NodeState execute() override {
       /* if (blackboard.get<bool>("playerDetected")) {
            return NodeState::SUCCESS;
        }*/
        return NodeState::FAILURE;
    }
};
