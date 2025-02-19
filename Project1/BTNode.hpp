#include "Blackboard.hpp"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;
using namespace sf;

enum class NodeState { SUCCESS, FAILURE, RUNNING };

class BTNode {
public:
    virtual ~BTNode() = default;
    virtual NodeState execute() = 0;
};