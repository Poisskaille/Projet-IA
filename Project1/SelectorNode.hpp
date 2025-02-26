#pragma once

#include "BehaviorNode.hpp"

class SelectorNode : public BehaviorNode {
public:
    void addChild(unique_ptr<BehaviorNode> child) {
        m_children.push_back(move(child));
    }

    bool execute() override {
        for (auto& child : m_children) {
            if (child->execute()) {
                return true;
            }
        }
        return false;
    }

private:
    vector<unique_ptr<BehaviorNode>> m_children;
};