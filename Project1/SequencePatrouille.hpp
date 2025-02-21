#pragma once
#include "BehaviorNode.hpp"

class SequencePatrouille : public BehaviorNode {
public:
    void addChild(unique_ptr<BehaviorNode> child) {
        m_children.push_back(move(child));
    }

    bool execute() override {
        for (auto& child : m_children) {
            if (!child->execute()) {
                return false;
            }
        }
        return true;
    }

private:
    vector<unique_ptr<BehaviorNode>> m_children;
};
