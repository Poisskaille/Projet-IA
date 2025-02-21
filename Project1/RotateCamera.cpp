#include "RotateCamera.hpp"
#include "CameraMGS.hpp"

bool RotateCamera::execute()
{
	camera.Rotate(0.016f);
	return true;
}
