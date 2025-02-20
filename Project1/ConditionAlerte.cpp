#include "ConditionAlerte.hpp"
#include "Player.hpp"
#include "CameraMGS.hpp"

bool ConditionAlerte::execute()
{
    if (camera.getVision().getGlobalBounds().intersects(player.shape.getGlobalBounds()) && player.SPEED >= 100.f) {
        return true;
    }
    return false;
}
