#pragma once
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class TraperEnemy : public Enemy {
public:
	TraperEnemy(float x, float y, Grid& grid);
	void update(float deltaTime, Grid& grid, const Vector2f& playerPos) override;
	void draw(RenderWindow& window);
	void RandomMove(float deltaTime, Grid& grid);
private:

	bool newRandomPos = false;
	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	float randomx = 0;
	float randomy = 0;

	Clock Delai;

	CircleShape mine_shape;
	vector<unique_ptr<CircleShape>> mines;
};


