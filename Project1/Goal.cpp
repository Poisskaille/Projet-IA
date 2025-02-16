#include "Goal.hpp"
using namespace std;

Goal::Goal(string name, int priority) : m_name(name), m_priority(priority) {}

int Goal::getPriority() const { return m_priority; }
string Goal::getName() const { return m_name; }

// Définition des objs
Goal goal_AttackPlayer("AttackPlayer", 3);
Goal goal_Reload("Reload", 2);
Goal goal_Patrol("Patrol", 1);
