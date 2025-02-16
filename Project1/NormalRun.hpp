#include "BTNode.hpp"
#include "PatrolMGS.hpp"

class NormalRun : public BTNode {
private:
    PatrolMGS* enemy;
public:
    NormalRun(PatrolMGS* enemy): enemy(enemy) {}
    NodeState execute() override {
        if (!enemy) return NodeState::FAILURE;

        enemy->Patrol(0.016f);

        return NodeState::SUCCESS;
    }
};