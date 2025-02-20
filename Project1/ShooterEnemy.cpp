#include "ShooterEnemy.hpp"
#include "ShootAction.hpp"
#include "MoveToReloadAction.hpp"
#include "ReloadAction.hpp"
#include "Goal.hpp"
#include "Grid.hpp"

ShooterEnemy::ShooterEnemy(float x, float y, Grid& grid) : Enemy(x, y), m_grid(grid) {
    shape.setFillColor(Color::Green);

    m_planner.addAction(new ShootAction(m_ammo));
    m_planner.addAction(new MoveToReloadAction(m_position, grid));
    m_planner.addAction(new ReloadAction(m_ammo));

    m_planner.addGoal(goal_AttackPlayer);
    m_planner.addGoal(goal_Reload);
    m_planner.addGoal(goal_Patrol);
}

void ShooterEnemy::update(float deltaTime, Grid& grid, const Vector2f& playerPos) {
    Action* action = m_planner.getBestAction();
    if (action) {
        action->execute();
    }
}

void ShooterEnemy::draw(RenderWindow& window)
{
    window.draw(shape);
}