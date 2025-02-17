#ifndef RELOAD_ACTION_HPP
#define RELOAD_ACTION_HPP

#include "Action.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ReloadAction : public Action {
public:
    ReloadAction(int& ammo);
    bool canExecute() override;
    void execute() override;

private:
    int& m_ammo;
};

#endif
