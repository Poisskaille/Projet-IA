#include <SFML/Graphics.hpp>
#include <iostream>
#include "EnemyManager.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Player.hpp"
#include <vector>

EnemyManager manager;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    srand(time(NULL));
    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(100, 500);
    //vector<Enemy> enemies = { Enemy(100, 100), Enemy(700, 100) };
    Grid grid;
    grid.loadFromFile("map.txt");
    grid.spawnEnemies(manager, "map2.txt");

    manager.createMGSPatrol(100, 300, { 2, 2 }, { 3, 15 }, { 14, 9 });
    manager.createMGSPatrol(600, 120, { 18, 3 }, { 10, 22 }, { 30, 6 });


    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            manager.setMenacedState();
        }

        if (Keyboard::isKeyPressed(Keyboard::X)) {
            manager.setNormalState();
        }

        player.update(deltaTime, grid,player.shape.getPosition());

        if (Keyboard::isKeyPressed(Keyboard::M)) {
            grid.switchMap(window, manager, "map.txt", "map2.txt");
        }

        if (Keyboard::isKeyPressed(Keyboard::L)) {
            grid.switchMap(window, manager, "map2.txt", "map.txt");
        }

        player.update(deltaTime, grid, player.shape.getPosition());

        window.clear();
        grid.draw(window);
        window.draw(player.getStunZone());
        window.draw(player.shape);
        manager.update(window,deltaTime,grid,player.shape.getGlobalBounds(),player.shape.getPosition(),player.SPEED,player.getStunZone().getGlobalBounds(),player.getStun());
        window.display();
    }

    return 0;
}

