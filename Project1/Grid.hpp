#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

class EnemyManager;

using namespace std;
using namespace sf;

const int GRID_WIDTH = 40;
const int GRID_HEIGHT = 30;
const int CELL_SIZE = 25;

struct Cell {
    bool walkable;
    Vector2f position;
    RectangleShape shape;
};

class Grid {
public:
    Grid();
    void loadFromFile(const string& filename);
    void draw(RenderWindow& window);
    void spawnEnemies(EnemyManager& manager, const string& enemyFile);
    void switchMap(EnemyManager& manager, const string& newMap, const string& newEnemyMap);
    Cell& getCell(int x, int y);
    bool isWalkable(sf::Vector2f pos);
private:
    vector<vector<Cell>> cells;
    string currentMap;
    string currentEnemyMap;
};

#endif      
