#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Grid.hpp"

using namespace std;
using namespace sf;

class BehaviorNode {
public:
    virtual ~BehaviorNode() = default;
    virtual bool execute() = 0;
};
