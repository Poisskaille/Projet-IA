#include "PatrolMGS.hpp"
#include "Grid.hpp"

PatrolMGS::PatrolMGS(float x, float y, Vector2i p1, Vector2i p2, Vector2i p3)
	: Enemy(x, y), m_position(x, y), m_p1(p1), m_p2(p2), m_p3(p3), m_currentWaypoint(0), m_state(State::NORMAL)
{
    
	shape.setSize({ 15, 15 });
	shape.setFillColor(Color::Green);
	shape.setPosition(m_position);
    shape.setOrigin(10, 10);
    m_sounddetection.setRadius(150);
    m_sounddetection.setPosition(shape.getPosition());
    m_sounddetection.setFillColor(Color(167, 255, 145, 30));
    m_sounddetection.setOrigin(150, 150);

}

PatrolMGS::~PatrolMGS(){}

void PatrolMGS::update(float deltaTime, Grid& grid, const Vector2f& playerPos)
{
    switch (m_state) {
    case State::NORMAL:
        Patrol(deltaTime,grid);
        break;
    case State::SPOTTED:
        if (m_time > 1) { Spotted(deltaTime,grid); } 
        break;
    case State::MENACE:
        RandomChase(deltaTime, grid);
        if (m_delay.getElapsedTime().asSeconds() > 10) { setNormalState(); newRandomPos = false; }
        break;
    case State::ALERTE:
            chase(playerPos, deltaTime, grid);
            cout << m_delay.getElapsedTime().asSeconds() << endl;
            if (m_delay.getElapsedTime().asSeconds() > 5) { setMenacedState(); }
            break;
    case State::STUNNED:
        if (m_delay.getElapsedTime().asSeconds() > 5) { setMenacedState(); }
        break;
    }
    if (!m_canMove) { m_time += deltaTime; }

}

void PatrolMGS::draw(RenderWindow& window)
{
    window.draw(shape);
    window.draw(m_sounddetection);
}

void PatrolMGS::Patrol(float deltaTime, Grid& grid) {
    Vector2i waypoints[3] = { m_p1, m_p2, m_p3 };
    Vector2i target = waypoints[m_currentWaypoint];

    if (m_path.empty() || m_path.back() != target) {
        m_path = pathfinding.findPath(grid, Vector2i(m_position.x / CELL_SIZE, m_position.y / CELL_SIZE), target);
        m_pathIndex = 0;
    }

    if (!m_path.empty() && m_pathIndex < m_path.size()) {
        Vector2f nextPos(m_path[m_pathIndex].x * CELL_SIZE, m_path[m_pathIndex].y * CELL_SIZE);
        Vector2f direction = nextPos - m_position;
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 5.f) {
            m_pathIndex++;
        }
        else {
            direction /= distance;
            m_direction = direction;
            m_position += direction * SPEED * deltaTime;
        }
    }
    else {
        m_canMove = false;
        if (m_time >= 2) {
            m_currentWaypoint = (m_currentWaypoint + 1) % 3;
            m_canMove = true;
            m_time = 0;
        }
    }

    if (m_canMove) {
        shape.setPosition(m_position);
        m_sounddetection.setPosition(shape.getPosition());
    }
}

void PatrolMGS::Spotted(float deltaTime, Grid& grid) {
    Vector2i playerGridPos(m_playerPos.x / CELL_SIZE, m_playerPos.y / CELL_SIZE);

    if (m_path.empty() || m_path.back() != playerGridPos) {
        m_path = pathfinding.findPath(grid, Vector2i(m_position.x / CELL_SIZE, m_position.y / CELL_SIZE), playerGridPos);
        m_pathIndex = 0;
    }

    if (!m_path.empty() && m_pathIndex < m_path.size()) {
        Vector2f nextPos(m_path[m_pathIndex].x * CELL_SIZE, m_path[m_pathIndex].y * CELL_SIZE);

        Vector2f direction = nextPos - m_position;
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 5.f) {
            m_pathIndex++;
            m_canMove = false;

        }
        else {
            direction /= distance;
            m_direction = direction;
            m_position += direction * SPEED * deltaTime;
        }

    }
    if (m_time >= 4) { m_canMove = true; isNormal = true; m_time = 0; setNormalState(); }

        shape.setPosition(m_position);
        m_sounddetection.setPosition(shape.getPosition());
}


void PatrolMGS::chase(const Vector2f& playerPos, float deltaTime, Grid& grid) {

    Vector2i playerGridPos(playerPos.x / CELL_SIZE, playerPos.y / CELL_SIZE);
    Vector2i enemyGridPos(m_position.x / CELL_SIZE, m_position.y / CELL_SIZE);

    if ((m_path.empty() || m_path.back() != playerGridPos) && chaseDelay.getElapsedTime().asSeconds() > 2.f) {
        m_path = pathfinding.findPath(grid, enemyGridPos, playerGridPos);
        m_pathIndex = 0;
        chaseDelay.restart();
    }

    if (!m_path.empty() && m_pathIndex < m_path.size()) {
        Vector2f nextPos(m_path[m_pathIndex].x * CELL_SIZE, m_path[m_pathIndex].y * CELL_SIZE);
        Vector2f direction = nextPos - m_position;
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 5.f) {
            m_pathIndex++;
        }
        else {
            direction /= distance;
            m_direction = direction;
            m_position += direction * SPEED * deltaTime;
        }
    }

    shape.setPosition(m_position);
    m_sounddetection.setPosition(shape.getPosition());
}


void PatrolMGS::RandomChase(float deltaTime, Grid& grid) {
    if (!newRandomPos) {
        bool validPosition = false;
        while (!validPosition) {
            randomx = rand() % 30;
            cout << "x : " << randomx << endl;
            randomy = rand() % 20;
            cout << "y : " << randomy << endl;
            if (grid.getCell(randomx, randomy).walkable) {
                validPosition = true;
            }
        }
        newRandomPos = true;
    }

    Vector2i target = { randomx, randomy };

    if (m_path.empty() || m_path.back() != target) {
        m_path = pathfinding.findPath(grid, Vector2i(m_position.x / CELL_SIZE, m_position.y / CELL_SIZE), target);
        m_pathIndex = 0;
    }

    if (!m_path.empty() && m_pathIndex < m_path.size()) {
        Vector2f nextPos(m_path[m_pathIndex].x * CELL_SIZE, m_path[m_pathIndex].y * CELL_SIZE);
        Vector2f direction = nextPos - m_position;

        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 5.f) {
            m_pathIndex++;
            if (m_pathIndex >= m_path.size()) {
                newRandomPos = false;
            }
        }
        else {
            direction /= distance;
            m_direction = direction;
            m_position += direction * SPEED * deltaTime;
        }
    }
    shape.setPosition(m_position);
    m_sounddetection.setPosition(shape.getPosition());
}

void PatrolMGS::setMenacedState()
{
    m_delay.restart();
    m_state = State::MENACE;
    m_time = 0.f;
	SPEED = 140.f;
	shape.setFillColor(Color::Yellow);
}

void PatrolMGS::setNormalState() {
    m_state = State::NORMAL;
	SPEED = 100.f;
	shape.setFillColor(Color::Green);
}

void PatrolMGS::setAlerteState() {
    m_delay.restart();
    m_state = State::ALERTE;
	SPEED = 125.f;
	shape.setFillColor(Color::Red);
}

void PatrolMGS::setSpottedState(const Vector2f& playerPos) {
    m_playerPos = playerPos;
    m_state = State::SPOTTED;
	SPEED = 100.f;
	shape.setFillColor(Color(107, 255, 250));
}

void PatrolMGS::setStunnedState() {
    m_delay.restart();
    m_state = State::STUNNED;
    m_time = 0.f;
    SPEED = 0.f;
    shape.setFillColor(Color(145, 156, 150));
}

void PatrolMGS::rayCasting(Grid& grid, RenderWindow& window) {
    float fov = 40.f;
    int numRays = 30;
    float maxDistancePrimary = 150.0f;
    float maxDistanceSecondary = 300.0f;

    float angleStart = -fov / 2.0f;
    float angleStep = fov / static_cast<float>(numRays - 1);

    m_primaryCone.setPointCount(numRays + 1);
    m_primaryCone.setFillColor(Color(150, 255, 243, 100));

    m_secondaryCone.setPointCount(numRays + 1);
    m_secondaryCone.setFillColor(Color(108, 217, 204, 50));

    m_primaryCone.setPoint(0, m_position);
    m_secondaryCone.setPoint(0, m_position);

    float baseAngle = atan2(m_direction.y, m_direction.x) * 180.f / 3.14159f;

    for (int i = 0; i < numRays; i++) {
        float angle = baseAngle + angleStart + i * angleStep;
        float rad = angle * 3.14159f / 180.0f;

        Vector2f direction(cos(rad), sin(rad));


        Vector2f rayPosPrimary = m_position;
        float distancePrimary = maxDistancePrimary;
        while (distancePrimary > 0) {
            rayPosPrimary += direction * 5.0f;
            distancePrimary -= 5.0f;

            int gridX = static_cast<int>(rayPosPrimary.x) / CELL_SIZE;
            int gridY = static_cast<int>(rayPosPrimary.y) / CELL_SIZE;

            if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
                break;
            }

            if (!grid.getCell(gridX, gridY).walkable) {
                break;
            }
        }

        Vector2f rayPosSecondary = m_position;
        float distanceSecondary = maxDistanceSecondary;
        while (distanceSecondary > 0) {
            rayPosSecondary += direction * 5.0f;
            distanceSecondary -= 5.0f;

            int gridX = static_cast<int>(rayPosSecondary.x) / CELL_SIZE;
            int gridY = static_cast<int>(rayPosSecondary.y) / CELL_SIZE;

            if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
                break;
            }

            if (!grid.getCell(gridX, gridY).walkable) {
                break;
            }
        }

        m_primaryCone.setPoint(i + 1, rayPosPrimary);
        m_secondaryCone.setPoint(i + 1, rayPosSecondary);
    }

    window.draw(m_secondaryCone);
    window.draw(m_primaryCone);
}

ConvexShape PatrolMGS::getFirstCasting() { return m_primaryCone; }
ConvexShape PatrolMGS::getSecondCasting(){ return m_secondaryCone; }
CircleShape PatrolMGS::getSoundDetection() { return m_sounddetection; }

void PatrolMGS::setTime(float time){ m_time = time; }

void PatrolMGS::setMove(bool value){ m_canMove = value; }

int PatrolMGS::getState()
{
    switch (m_state) {
    case State::ALERTE:
        return 1;
        break;
    case State::STUNNED:
        return 2;
        break;
    }
}
