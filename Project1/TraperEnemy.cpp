#include "TraperEnemy.hpp"

//#include "Grid.hpp"

TraperEnemy::TraperEnemy(float x, float y, Grid& grid) : Enemy(x, y), m_position(x, y) {
	shape.setFillColor(Color::Blue);
}

void TraperEnemy::update(float deltaTime, Grid& grid, const Vector2f& playerPos) {
    RandomMove(deltaTime, grid);
    if (Delai.getElapsedTime().asSeconds() >= 2) {
        auto mine = std::make_unique<sf::CircleShape>(10.f);
        mine->setFillColor(sf::Color::Red);
        mine->setPosition(shape.getPosition());

        mines.push_back(std::move(mine));

        Delai.restart();
    }

}

void TraperEnemy::RandomMove(float deltaTime, Grid& grid) {
    if (!newRandomPos) {
         randomx = rand() % 600;
         randomy = rand() % 600;
         cout << "x :" << randomx << endl;
         cout << "y :" << randomy << endl;
        newRandomPos = true;
    }

    Vector2f target = { randomx, randomy };
    Vector2f direction = target - m_position;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.f) {
        newRandomPos = false;
    }
    else {
        direction /= distance;
        m_direction = direction;
        m_position += direction * SPEED * deltaTime;
    }
    shape.setPosition(m_position);
}

void TraperEnemy::draw(RenderWindow& window)
{
	window.draw(shape);
    for (auto& mine : mines) {
        window.draw(*mine);
    }
}
