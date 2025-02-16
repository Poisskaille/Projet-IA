#include "PatrolMGS.hpp"

PatrolMGS::PatrolMGS(float x, float y, Vector2f p1, Vector2f p2, Vector2f p3)
	: Enemy(x, y), m_position(x, y), m_p1(p1), m_p2(p2), m_p3(p3), m_currentWaypoint(0)
{

	shape.setSize({ 20, 20 });
	shape.setFillColor(Color::Magenta);
	shape.setPosition(m_position);
}

PatrolMGS::~PatrolMGS()
{
}

void PatrolMGS::update(float deltaTime, Grid& grid)
{
	Patrol(deltaTime);
	if (!m_canMove) {m_time += deltaTime;}
}

void PatrolMGS::Patrol(float deltaTime) {
	Vector2f waypoints[3] = { m_p1, m_p2, m_p3 };
	Vector2f target = waypoints[m_currentWaypoint];
	Vector2f direction = target - m_position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance < 5.0f) {
		m_canMove = false;
		if (m_time >= 2) { m_currentWaypoint = (m_currentWaypoint + 1) % 3; m_canMove = true; m_time = 0; }		
	}
	else {
		direction /= distance;
        m_direction = direction;

		m_position += direction * 2.0f;
	}

	if (m_canMove) {shape.setPosition(m_position);}
	
}

void PatrolMGS::setMenacedState()
{
	SPEED = 150.f;
	shape.setFillColor(Color::Yellow);
}

void PatrolMGS::setNormalState() {
	SPEED = 100.f;
	shape.setFillColor(Color::Green);
}

void PatrolMGS::setAlerteState() {
	SPEED = 200.f;
	shape.setFillColor(Color::Red);
}

void PatrolMGS::setSpottedState() {
	SPEED = 100.f;
	shape.setFillColor(Color(221, 235, 23));
}

void PatrolMGS::rayCasting(Grid& grid, RenderWindow& window) {
    float fov = 40.f;
    int numRays = 30;
    float maxDistance = 150.0f;

    float angleStart = -fov / 2.0f;
    float angleStep = fov / static_cast<float>(numRays - 1);

    m_cone.setPointCount(numRays + 1);
    m_cone.setFillColor(Color(150, 255, 243, 100));

    m_cone.setPoint(0, m_position);

    float baseAngle = atan2(m_direction.y, m_direction.x) * 180.f / 3.14159f;

    for (int i = 0; i < numRays; i++) {
        float angle = baseAngle + angleStart + i * angleStep;
        float rad = angle * 3.14159f / 180.0f;

        Vector2f direction(cos(rad), sin(rad));
        Vector2f rayPos = m_position;

        float distance = maxDistance;
        while (distance > 0) {
            rayPos += direction * 5.0f;
            distance -= 5.0f;

            int gridX = static_cast<int>(rayPos.x) / CELL_SIZE;
            int gridY = static_cast<int>(rayPos.y) / CELL_SIZE;

            if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
                break;
            }

            if (!grid.getCell(gridX, gridY).walkable) {
                break;
            }
        }

        m_cone.setPoint(i + 1, rayPos);
    }

    window.draw(m_cone);
}

ConvexShape PatrolMGS::getCasting()
{
    return m_cone;
}
