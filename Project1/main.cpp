#include <SFML/Graphics.hpp>
#include "EnemyManager.hpp"
#include "TraperEnemy.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Player.hpp"
#include "CameraMGS.hpp"




FootStepManager stepmanager;
EnemyManager manager;
GOAPAgent enemyAgent;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    srand(time(NULL));
    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(100, 500);
    //vector<Enemy> enemies = { Enemy(100, 100), Enemy(700, 100) };
    Grid grid;
    grid.loadFromFile("map.txt",manager);

    CameraMGS camera1({ 700,500 }, 90, 280);
    camera1.initTree(grid, manager, player);
    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        enemyAgent.PerformAction();
        
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

        if (Keyboard::isKeyPressed(Keyboard::M)) {
            grid.loadFromFile("map2.txt", manager);
            player.shape.setPosition(100, 100);
            camera1.setDrawable(false);
        }

        if (Keyboard::isKeyPressed(Keyboard::L)) {
            grid.loadFromFile("map.txt", manager);
            player.shape.setPosition(100, 500);
            camera1.setDrawable(true);
        }

        if (Keyboard::isKeyPressed(Keyboard::K)) {
            grid.loadFromFile("map3.txt", manager);
                player.shape.setPosition(100, 500);
        }


        player.update(deltaTime, grid, player.shape.getPosition());

        window.clear();
        grid.draw(window);
        stepmanager.draw(window);
        stepmanager.update();

        window.draw(player.getStunZone());
        window.draw(player.shape);
        manager.update(window,deltaTime,grid,player.shape.getGlobalBounds(),player.shape.getPosition(),player.SPEED,player.getStunZone().getGlobalBounds(),player.getStun(), player);

        camera1.update(deltaTime,grid);
        camera1.draw(window);
        window.display();
    }

    return 0;
}

