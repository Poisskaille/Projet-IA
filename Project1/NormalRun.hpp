#include "BTNode.hpp"

class NormalRun : public BTNode {
private:
public:
    NormalRun() {}
    NodeState execute() override {
        // Va de point en point
        return NodeState::SUCCESS;
    }
};