#pragma once

#include "BehaviorNode.hpp"

class EnemyManager;

class AlerteAll : public BehaviorNode {
public:

	AlerteAll(EnemyManager& manager): manager(manager){}

	bool execute() override;

private:

	EnemyManager& manager;
};