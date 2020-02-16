
#pragma once

#include "Common.h"
#include "Repository.h"
#include "FrameSystem.h"
#include "Player.h"
#include "Board.h"
#include "Controllers.h"

namespace C35
{
struct Conductor : public UpdateTarget, InputTarget
{
	Conductor(Ref<Player>          player,
			  Board&               board,
			  FramePtr             owner,
			  AnimationController& animationController,
			  DisplayController&   displayController,
			  InputController&     inputController)
		: player(player), board(board), owner(owner), animationController(animationController),
		  displayController(displayController), inputController(inputController)
	{}

protected:
	Ref<Player> player;
	Board&      board;
	FramePtr    owner;

	AnimationController& animationController;
	DisplayController&   displayController;
	InputController&     inputController;
};

}  // namespace C35
