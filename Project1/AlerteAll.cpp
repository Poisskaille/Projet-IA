#include "AlerteAll.hpp"
#include "EnemyManager.hpp"

bool AlerteAll::execute()
{
    manager.setMenacedState();
    return true;;
}
