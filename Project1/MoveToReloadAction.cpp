#include "MoveToReloadAction.hpp"
#include <iostream>

MoveToReloadAction::MoveToReloadAction(Vector2f& position, Grid& grid)
    : Action("MoveToReload", 3.0f), m_position(position), m_grid(grid) {
}

bool MoveToReloadAction::canExecute() {
    return true;
}

void MoveToReloadAction::execute() {
    std::cout << "Enemy moves to reload station..." << std::endl;
    // Trouver une case de rechargement "R" et s'y déplacer
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (m_grid.getCell(x, y).shape.getFillColor() == sf::Color::Red) {
                m_position = sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
                return;
            }
        }
    }
}
