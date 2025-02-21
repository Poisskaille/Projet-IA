#ifndef SHOOTER_ENEMY_HPP
#define SHOOTER_ENEMY_HPP

#include "GOAPPlanner.hpp"
#include "ShootAction.hpp"
#include "MoveToReloadAction.hpp"
#include "ReloadAction.hpp"
#include "State.hpp"
#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "GOAPAgent.hpp"

using namespace sf;

class ShooterEnemy {
protected:
    GOAPPlanner planner;
    RectangleShape shape;
    Vector2f position;

public:
    State state;
    GOAPAgent agent;
    GOAPAgent& getAgent() { return agent; }

    ShooterEnemy(float x, float y) {
        shape.setSize(Vector2f(20.f, 20.f));
        shape.setFillColor(Color::Red);
        shape.setPosition(x, y);
        position = { x, y };
    }

    class Projectile {
    public:
        CircleShape shape;
        Vector2f velocity;

        Projectile(Vector2f pos, Vector2f dir) {
            shape.setRadius(5.f);
            shape.setFillColor(Color::Yellow);
            shape.setPosition(pos);
            velocity = dir * 500.f;
        }

        void update(float deltaTime) {
            shape.move(velocity * deltaTime);
        }
    };

    std::vector<Projectile> projectiles;


    void update(float deltaTime, Vector2f playerPos, Grid& grid) {
        agent.PerformAction(state);

        if (state.Empthy()) {
            Vector2f reloadPos = grid.findReloadZone();
            std::cout << "[ShooterEnemy] Recherche de la zone 'R' : ("
                << reloadPos.x << ", " << reloadPos.y << ")" << std::endl;
            if (reloadPos.x != -1 && reloadPos.y != -1) {
                std::cout << "[ShooterEnemy] Zone de recharge détectée à : "
                    << reloadPos.x << ", " << reloadPos.y << std::endl;
                Vector2f reloadDir = reloadPos - shape.getPosition();
                float reloadLength = sqrt(reloadDir.x * reloadDir.x + reloadDir.y * reloadDir.y);

                if (reloadLength > 1.0f) {
                    reloadDir /= reloadLength;
                    if (grid.isWalkable(reloadPos)) {
                        std::cout << "[ShooterEnemy] Déplacement vers la zone de recharge.\n";
                        shape.move(reloadDir * 50.0f * deltaTime);
                    }
                    else {
                        std::cout << "[ShooterEnemy] Zone non accessible !\n";
                    }
                }
            }
        }
        else if (state.AmmoFind()) {
            std::cout << "[ShooterEnemy] Rechargement en cours...\n";
            state.Reload(5);
            state.ammoFind = false;
        }

        else if (!state.Empthy()) {
            Vector2f direction = playerPos - shape.getPosition();
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);

            if (length > 1.0f) {
                direction /= length;
                shape.move(direction * 30.0f * deltaTime);
            }

            if (length < 500.f) {
                static Clock fireClock;
                if (fireClock.getElapsedTime().asSeconds() > 1.0f) {
                    projectiles.emplace_back(shape.getPosition(), direction);
                    state.Shoot(1);
                    std::cout << "[ShooterEnemy] Tir effectué. Munitions restantes : " << state.Ammo() << "\n";
                    fireClock.restart();
                }
            }
        }

        for (auto& projectile : projectiles) {
            projectile.update(deltaTime);
        }

        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
            [](const Projectile& p) {
                auto pos = p.shape.getPosition();
                return (pos.x < 0 || pos.x > 800 || pos.y < 0 || pos.y > 600);
            }), projectiles.end());
    }


    void draw(RenderWindow& window) {
        window.draw(shape);
        for (auto& projectile : projectiles) {
            window.draw(projectile.shape);
        }
    }

    std::vector<Projectile>& getProjectiles() { return projectiles; }
};

#endif
