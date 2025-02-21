#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

class Player;
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
    bool isReloadZone = false;
};

class Grid {
public:
    Grid();
    void loadFromFile(const string& filename, EnemyManager& manager);
    void draw(RenderWindow& window);
    void spawnEnemies(EnemyManager& manager, const string& enemyFile);

    Cell& getCell(int x, int y);
    bool isWalkable(Vector2f pos);
    Vector2f findReloadZone();
private:
    vector<vector<Cell>> cells;
    string currentMap;
    string currentEnemyMap;
};

#endif      
