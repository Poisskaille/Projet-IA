#include "Entity.hpp"

Entity::Entity(float x, float y, Color color) {
    shape.setSize({ 15 , 15 });
    shape.setPosition(x, y);
    shape.setFillColor(color);
}
