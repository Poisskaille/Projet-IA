#ifndef ACTION_HPP
#define ACTION_HPP
#include "State.hpp"
#include <iostream>

class Action {
public:
    virtual bool canExecute(const State& state) = 0;
    virtual void execute(State& state) = 0;
    virtual ~Action() = default;
};

#endif