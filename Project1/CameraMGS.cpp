#include "CameraMGS.hpp"

CameraMGS::CameraMGS(Vector2f spawnPos, float minAngle, float maxAngle)
{
	m_minAngle = minAngle;
	m_maxAngle = maxAngle;
	m_currentAngle = m_minAngle;
	m_shape.setPosition(spawnPos);
	m_shape.setSize({ 10,10 });
	m_shape.setFillColor(Color::Yellow);
	m_shape.setRotation(m_minAngle);
	m_shape.setOrigin(5, 5);
}

CameraMGS::~CameraMGS()
{
}

void CameraMGS::update(float deltaTime, Grid& grid)
{
    if (isDrawable) {
        if (m_root) {
            m_root->execute();
        }
        rayCasting(grid);
    }  
}

void CameraMGS::initTree(Grid& grid, EnemyManager& manager, Player& player)
{
    m_root = make_unique<SelectorNode>();
    rotateAction = make_unique<RotateCamera>(*this, grid);

    sequencePatrouille = make_unique<SequencePatrouille>();
    sequencePatrouille->addChild(move(rotateAction));

    //

    alerteAction = make_unique<AlerteAll>(manager);

    sequenceAlerte = make_unique<SequenceAlerte>();
    conditionAlerte = make_unique<ConditionAlerte>(*this, player);

    sequenceAlerte->addChild(move(conditionAlerte));
    sequenceAlerte->addChild(move(alerteAction));

    m_root->addChild(move(sequenceAlerte));
    m_root->addChild(move(sequencePatrouille));
}


void CameraMGS::Rotate(float deltaTime) {
    if (!m_reverseSwing) {
        m_currentAngle += deltaTime * 20;
        if (m_currentAngle >= m_maxAngle) {
            m_currentAngle = m_maxAngle;
            m_reverseSwing = true;
        }
    }
    else {
        m_currentAngle -= deltaTime * 20;
        if (m_currentAngle <= m_minAngle) {
            m_currentAngle = m_minAngle;
            m_reverseSwing = false;
        }
    }
    m_shape.setRotation(m_currentAngle);
}


void CameraMGS::draw(RenderWindow& window) {
    if (isDrawable) {
        window.draw(m_shape); window.draw(m_vision);
    }
}

void CameraMGS::rayCasting(Grid& grid) {
    float fov = 20.f;
    int numRays = 30;
    float maxDistance = 150.0f;

    float angleStart = -fov / 2.0f;
    float angleStep = fov / static_cast<float>(numRays - 1);

    Vector2f cameraPos = m_shape.getPosition();
    m_vision.setPointCount(numRays + 2);
    m_vision.setFillColor(Color(255, 0, 0, 100));
    m_vision.setPoint(0, cameraPos);

    float baseAngleRad = m_currentAngle * 3.14159f / 180.0f;

    for (int i = 0; i <= numRays; i++) {
        float angle = baseAngleRad + (angleStart + i * angleStep) * 3.14159f / 180.0f;
        Vector2f direction(cos(angle), sin(angle));

        Vector2f rayPos = cameraPos;
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
        m_vision.setPoint(i + 1, rayPos);
    }
}

ConvexShape CameraMGS::getVision()
{
    return m_vision;
}

void CameraMGS::setDrawable(bool value)
{
    isDrawable = value;
}
