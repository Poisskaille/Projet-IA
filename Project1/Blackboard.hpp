#include <iostream>
#include <string>

using namespace std;

enum class EnemyState {NORMAL, SPOTTER, MENACE, ALERTE,};

class Blackboard {
private:
    EnemyState currentState;

public:
    Blackboard() : currentState(EnemyState::NORMAL) {}

    EnemyState getState() const { return currentState; }
    void setState(EnemyState newState) { currentState = newState; }

};