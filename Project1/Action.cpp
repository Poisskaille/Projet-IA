#include "Action.hpp"
using namespace std;

Action::Action(string name, float cost) : m_name(name), m_cost(cost) {}

float Action::getCost() const { return m_cost; }
string Action::getName() const { return m_name; }
