#include "ReloadAction.hpp"
#include <iostream>

ReloadAction::ReloadAction(int& ammo) : Action("Reload", 2.0f), m_ammo(ammo) {}

bool ReloadAction::canExecute() {
    return m_ammo == 0;
}

void ReloadAction::execute() {
    std::cout << "Enemy reloading..." << std::endl;
    m_ammo = 5;
}
