#include "Entity.hpp"
#include "Grid.hpp"

Entity::Entity(float x, float y, Color color) {
    shape.setSize({ 20 , 20 });
    shape.setPosition(x, y);
    shape.setFillColor(color);
}
