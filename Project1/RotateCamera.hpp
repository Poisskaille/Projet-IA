#pragma once

#include "BehaviorNode.hpp"

class CameraMGS;

class RotateCamera : public BehaviorNode {
public:

	RotateCamera(CameraMGS& cam, Grid& grid1): camera(cam), grid(grid1){}

	bool execute() override;

private:
	CameraMGS& camera;
	Grid& grid;
};