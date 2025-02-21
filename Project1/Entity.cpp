#include "Entity.hpp"
#include "Grid.hpp"

Entity::Entity(float x, float y) {
    shape.setSize({ 15 , 15 });
    shape.setPosition(x, y);
}
