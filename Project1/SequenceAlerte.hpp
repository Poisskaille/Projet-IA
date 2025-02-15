#include "BTNode.hpp"

class SequenceAlerte : public BTNode {
private:
    vector<unique_ptr<BTNode>> children;
public:
    void AddChild(unique_ptr<BTNode> child) {
        children.push_back(move(child));
    }
    NodeState execute() override {
        for (auto& child : children) {
            if (child->execute() == NodeState::FAILURE) {
                return NodeState::FAILURE;
            }
        }
        return NodeState::SUCCESS;
    }
};