#ifndef ACTION_HPP
#define ACTION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
using namespace std;

class Action {
public:
    Action(string name, float cost);
    virtual ~Action() = default;

    float getCost() const;
    string getName() const;

    virtual bool canExecute() = 0;
    virtual void execute() = 0;

protected:
    string m_name;
    float m_cost;
};

#endif
