#pragma once
#include "BehaviorNode.hpp"

class CameraMGS;
class Player;

class ConditionAlerte : public BehaviorNode {
private:

    CameraMGS& camera;
    Player& player;

public:
    ConditionAlerte(CameraMGS& cam, Player& player):camera(cam), player(player){}
    bool execute() override;
};