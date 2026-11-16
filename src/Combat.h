
#pragma once

#include <variant>
#include <vector>

#include "Common.h"
#include "Unit.h"
#include "Player.h"
#include "Repository.h"


namespace C35
{


struct MoveCommand {
	Ref<Unit> unit;
	Pos destination;
};

struct AttackCommand {
	Ref<Unit> attacker;
	Ref<Unit> defender;
};

struct FortifyCommand {
	Ref<Unit> unit;
};

struct EndTurnCommand {
	Ref<Player> player;
};

using GameCommand = std::variant<
	MoveCommand,
	AttackCommand,
	FortifyCommand,
	EndTurnCommand
>;



struct CombatSystem
{
};

struct CombatResult
{
};

}

