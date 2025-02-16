#include <iostream>
#include <vector>
#include <memory>
#include "Blackboard.hpp"
#include "Player.hpp"

class PatrolMGS;
 
enum class NodeState { SUCCESS, FAILURE, RUNNING };

class BTNode {
public:
    virtual ~BTNode() = default;
    virtual NodeState execute() = 0;
};