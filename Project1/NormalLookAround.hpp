#include "BTNode.hpp"

class NormalLook : public BTNode {
private:
public:
    NormalLook() {}
    NodeState execute() override {
        // Fait un tour sur lui meme
        return NodeState::SUCCESS;
    }
};