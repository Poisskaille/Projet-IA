#include <SFML/Graphics.hpp>
#include <iostream>
#include "EnemyManager.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include <vector>
#include "BTNode.hpp"

EnemyManager manager;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    //vector<Enemy> enemies = { Enemy(100, 100), Enemy(700, 100) };
    Grid grid;
    grid.loadFromFile("map.txt");

    manager.createMGSPatrol(100, 300, {100,100}, {500,200},{300,300});
    manager.createMGSPatrol(600,120, {300,300}, {600,200}, {100,100});

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

        window.clear();
        grid.draw(window);
        window.draw(player.getStunZone());
        window.draw(player.shape);
        manager.update(window,deltaTime,grid,player.shape.getGlobalBounds(),player.shape.getPosition(),player.SPEED,player.getStunZone().getGlobalBounds(),player.getStun());
        window.display();
    }
    return 0;
}

