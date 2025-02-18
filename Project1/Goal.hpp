#ifndef GOAL_HPP
#define GOAL_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;

class Goal {
public:
    Goal(string name, int priority);
    int getPriority() const;
    string getName() const;

private:
    string m_name;
    int m_priority;
};

extern Goal goal_AttackPlayer;
extern Goal goal_Reload;
extern Goal goal_Patrol;
#endif
