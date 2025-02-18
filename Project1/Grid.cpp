
#include "Grid.hpp"
#include "EnemyManager.hpp"
#include <fstream>
#include <iostream>

Grid::Grid() {
    cells.resize(GRID_HEIGHT, vector<Cell>(GRID_WIDTH, { true, {0.f, 0.f}, RectangleShape(Vector2f(CELL_SIZE, CELL_SIZE)) }));
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cells[y][x].position = Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            cells[y][x].shape.setPosition(cells[y][x].position);
            cells[y][x].shape.setFillColor(Color::Transparent);
            cells[y][x].shape.setOutlineThickness(1);
            cells[y][x].shape.setOutlineColor(Color(50, 50, 50));
        }
    }
}

void Grid::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        string line;
        if (!getline(file, line)) break;
        for (int x = 0; x < GRID_WIDTH && x < line.size(); ++x) {
            cells[y][x].walkable = (line[x] == '0');
            if (!cells[y][x].walkable) {    
                cells[y][x].shape.setFillColor(Color::White);
            }
        }
    }
}

void Grid::spawnEnemies(EnemyManager& manager, const string& enemyFile) {
    ifstream file("map.txt");
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir map.txt" << endl;
        return;
    }

    int y = 0;
    string line;
    while (getline(file, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '2') {
                manager.createShooterEnemy(x * CELL_SIZE, y * CELL_SIZE, *this);
            }
        }
        y++;
    }
    file.close();
}

void Grid::switchMap(EnemyManager& manager, const string& newMap, const string& newEnemyMap) {
    cout << "Changement de carte vers : " << newMap << " et " << newEnemyMap << endl;

    loadFromFile(newMap);
    currentMap = newMap;

    manager.deleteAllEnemy();

    spawnEnemies(manager, newEnemyMap);
    currentEnemyMap = newEnemyMap;
}

void Grid::draw(RenderWindow& window) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            window.draw(cells[y][x].shape);
        }
    }
}

Cell& Grid::getCell(int x, int y) {
    return cells[y][x];
}

bool Grid::isWalkable(sf::Vector2f pos) {
    int x = static_cast<int>(pos.x / CELL_SIZE);  // Conversion en index de cellule
    int y = static_cast<int>(pos.y / CELL_SIZE);  // Conversion en index de cellule
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
        return false;
    return cells[y][x].walkable;
}
