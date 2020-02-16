
#pragma once

#include <vector>
#include <utility>

#include "Common.h"
#include "FrameSystem.h"

namespace C35
{

struct AnimationController : UpdateTarget
{
protected:
	std::vector<AnimationController*> subcontrollers;
};

struct DisplayController : UpdateTarget
{
protected:
	std::vector<DisplayController*> subcontrollers;
};

struct InputController : InputTarget
{
protected:
	std::vector<InputController*> subcontrollers;
};

}  // namespace C35

