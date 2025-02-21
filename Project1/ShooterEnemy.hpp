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
    State state;
    GOAPPlanner planner;
    RectangleShape shape;
    Vector2f position;
    GOAPAgent agent;

public:

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
            velocity = dir * 500.f;  // Vitesse du projectile
        }

        void update(float deltaTime) {
            shape.move(velocity * deltaTime);
        }
    };

    std::vector<Projectile> projectiles;


    void update(float deltaTime, Vector2f playerPos, Grid& grid) {
        agent.PerformAction();

        // 1. Si les munitions sont vides, chercher la zone de recharge
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
                else {
                    std::cout << "[ShooterEnemy] Zone atteinte. Rechargement...\n";
                    state.Reload(5);
                }
            }
        }

        // 2. Si les munitions ont été trouvées (zone atteinte), recharger
        else if (state.AmmoFind()) {
            std::cout << "[ShooterEnemy] Rechargement en cours...\n";
            state.Reload(5);  // Recharge complète
            state.ammoFind = false;  // Munitions trouvées, prêt à tirer
        }

        // 3. Si l'ennemi a des munitions, poursuivre le joueur et tirer
        else if (state.Ammo() > 0) {
            Vector2f direction = playerPos - shape.getPosition();
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);

            // Déplacement vers le joueur
            if (length > 1.0f) {
                direction /= length;
                shape.move(direction * 30.0f * deltaTime);
            }

            // Tir si le joueur est à portée
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

        // 4. Mise à jour des projectiles
        for (auto& projectile : projectiles) {
            projectile.update(deltaTime);
        }

        // 5. Supprimer les projectiles hors écran
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
