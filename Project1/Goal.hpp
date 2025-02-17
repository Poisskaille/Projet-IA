#ifndef GOAL_HPP
#define GOAL_HPP

#include <string>
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

#endif
