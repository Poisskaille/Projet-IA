#ifndef SHOOT_ACTION_HPP
#define SHOOT_ACTION_HPP

#include "Action.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ShootAction : public Action {
public:
    ShootAction(int& ammo);
    bool canExecute() override;
    void execute() override;

private:
    int& m_ammo;
};

#endif
