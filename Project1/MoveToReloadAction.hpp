#ifndef MOVE_TO_RELOAD_ACTION_HPP
#define MOVE_TO_RELOAD_ACTION_HPP

#include "Action.hpp"
#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class MoveToReloadAction : public Action {
public:
    MoveToReloadAction(Vector2f& position, Grid& grid);
    bool canExecute() override;
    void execute() override;

private:
    Vector2f& m_position;
    Grid& m_grid;
};

#endif
