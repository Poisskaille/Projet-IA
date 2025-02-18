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

void Grid::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }
    cout << "Chargement de la carte : " << filename << endl;
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        string line;
        if (!getline(file, line)) break;
        for (int x = 0; x < GRID_WIDTH && x < line.size(); ++x) {
            cells[y][x].walkable = (line[x] == '0' || line[x] == '2');
            if (!cells[y][x].walkable) {    
                cells[y][x].shape.setFillColor(Color::White);
            }
        }
    }
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
        }
        y++;
    }
    file.close();
}

void Grid::switchMap(RenderWindow& window, EnemyManager& manager, const string& newMap, const string& newEnemyMap, Player& player) {
    cout << "D�but du switchMap()" << endl;

    // Supprimer les ennemis de l'ancienne carte
    manager.deleteAllEnemy();
    cout << "Ennemis supprim�s" << endl;

    // R�initialiser la grille
    cells.clear();
    cells.resize(GRID_HEIGHT, vector<Cell>(GRID_WIDTH));

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cells[y][x].walkable = true; // Par d�faut, sol accessible
            cells[y][x].position = Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            cells[y][x].shape = RectangleShape(Vector2f(CELL_SIZE, CELL_SIZE));
            cells[y][x].shape.setPosition(cells[y][x].position);
            cells[y][x].shape.setFillColor(Color::Transparent); // Sol invisible par d�faut
            cells[y][x].shape.setOutlineThickness(1);
            cells[y][x].shape.setOutlineColor(Color(50, 50, 50));
        }
    }


    // Charger la nouvelle map
    loadFromFile(newMap);
    currentMap = newMap;
    cout << "Carte charg�e : " << currentMap << endl;

    // Nettoyage et redessinage de la fen�tre
    window.clear();
    draw(window);
    window.display();
    cout << "Nouvelle carte affich�e" << endl;

    // Charger les nouveaux ennemis
    spawnEnemies(manager, newEnemyMap);
    currentEnemyMap = newEnemyMap;
    cout << "Ennemis charg�s depuis : " << currentEnemyMap << endl;

    // Repositionner le joueur
    player.shape.setPosition(100, 100);
    cout << "Joueur repositionn�" << endl;
}



void Grid::draw(RenderWindow& window) {
    cout << "Affichage de la carte : " << currentMap << endl;
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
