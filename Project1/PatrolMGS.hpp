#ifndef PATROLMGS_HPP
#define PATROLMGS_HPP

#include "Enemy.hpp"
#include "Pathfinding.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;
class Grid;


class PatrolMGS : public Enemy {
public:

    enum class State { NORMAL, MENACE, ALERTE, SPOTTED, STUNNED };

    PatrolMGS(float x, float y, Vector2i p1, Vector2i p2, Vector2i p3);
    ~PatrolMGS();

    void update(float deltaTime, Grid& grid, const Vector2f& playerPos) override;
    void draw(RenderWindow& window);

    void Patrol(float deltaTime, Grid& grid);
    void Spotted(float deltaTime);
    void chase(const Vector2f& playerPos,float deltaTime);

    void setMenacedState();
    void setNormalState();
    void setAlerteState();
    void setSpottedState(const Vector2f& playerPos);
    void setStunnedState();

    void rayCasting(Grid& grid, RenderWindow& window);

    ConvexShape getFirstCasting();
    ConvexShape getSecondCasting();
    CircleShape getSoundDetection();

    void setTime(float time);
    void setMove(bool value);

    int getState();
    Clock m_delay;
    Pathfinding pathfinding;
private:
    
    float SPEED = 100.0f;
    bool m_canMove = true;

    Vector2f m_position;
    Vector2f m_direction;
    Vector2f m_playerPos;
   
    vector<Vector2i>m_path;
    int m_pathIndex = 0;
    int m_currentWaypoint;
    Vector2i m_p1, m_p2, m_p3;
    
    ConvexShape m_primaryCone;
    ConvexShape m_secondaryCone;

    CircleShape m_sounddetection;

    float m_time = 0;
    bool isNormal = true;

    State m_state;

};
#endif