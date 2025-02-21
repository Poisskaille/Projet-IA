#include "Grid.hpp"
#include "EnemyManager.hpp"
#include <fstream>
#include <iostream>
#include "Player.hpp"

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

void Grid::loadFromFile(const string& filename, EnemyManager& manager) {

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cells[y][x].walkable = true;
            cells[y][x].shape.setFillColor(Color::Transparent);
        }
    }
    manager.deleteAllEnemy();
    
    ifstream file(filename);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        string line;
        if (!getline(file, line)) break;
        for (int x = 0; x < GRID_WIDTH && x < line.size(); ++x) {
            cells[y][x].walkable = (line[x] == '0' || line[x] == '2' || line[x] == '3' || line[x] == '4');
            if (line[x] == 'R') {
                cells[y][x].shape.setFillColor(Color::Magenta);
                cells[y][x].isReloadZone = true;
                cells[y][x].walkable = true;
            }
            if (!cells[y][x].walkable) {    
                cells[y][x].shape.setFillColor(Color::White);
            }
        }
    }
    spawnEnemies(manager, filename);
}

Vector2f Grid::findReloadZone() {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            if (cells[y][x].isReloadZone) {
                return cells[y][x].position;
            }
        }
    }
    return Vector2f(-1, -1);
}

void Grid::spawnEnemies(EnemyManager& manager, const string& enemyFile) {
    ifstream file(enemyFile);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir map2.txt" << endl;
        return;
    }
    cout << "Chargement des ennemis depuis : " << enemyFile << endl;
    int y = 0;
    string line;
    while (getline(file, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '2') {
                manager.createShooterEnemy(x * CELL_SIZE, y * CELL_SIZE, *this);
            }
            if (line[x] == '3') {
                manager.createMGSPatrol(100, 100, { 2, 2 }, { 3, 15 }, { 14, 9 });
            }
            if (line[x] == '4') {
                manager.createMGSPatrol(600, 120, { 18, 3 }, { 10, 22 }, { 30, 6 });
            }
        }
        y++;
    }
    file.close();
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

bool Grid::isWalkable(Vector2f pos) {
    int x = static_cast<int>(pos.x / CELL_SIZE);
    int y = static_cast<int>(pos.y / CELL_SIZE);
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
        return false;
    return cells[y][x].walkable;
}
