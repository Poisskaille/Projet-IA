#include "ShootAction.hpp"
#include <iostream>

ShootAction::ShootAction(int& ammo) : Action("Shoot", 1.0f), m_ammo(ammo) {}

bool ShootAction::canExecute() {
    return m_ammo > 0;
}

void ShootAction::execute() {
    std::cout << "Enemy shoots!" << std::endl;
    m_ammo--;
}
