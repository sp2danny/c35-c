
#pragma once

#include "Common.h"
#include "Repository.h"
#include "FrameSystem.h"
#include "Player.h"
#include "Board.h"

namespace C35 {

struct Conductor : public UpdateTarget, InputTarget
{
	Conductor(Ref<Player> player, Board& board, FramePtr owner)
		: player(player), board(board), owner(owner)
	{}



protected:
	Ref<Player> player;
	std::reference_wrapper<Board> board;
	FramePtr owner;
};


}  // namespace C35

