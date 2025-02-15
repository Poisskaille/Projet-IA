#include <iostream>
#include <vector>
#include <memory>
#include "EnemyManager.hpp"
#include "Blackboard.hpp"
 
enum class NodeState { SUCCESS, FAILURE, RUNNING };

class BTNode {
public:
    virtual ~BTNode() = default;
    virtual NodeState execute() = 0;
};