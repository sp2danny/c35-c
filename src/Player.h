
#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "Common.h"
#include "Repository.h"

namespace C35
{

struct Unit;

struct Player : RepositoryBase<Player>
{

	UC color;

	City* capital;

	Board* game;

	Player(UC col, Board& b, bool pak)
		: color(col), capital(nullptr), game(&b), gold(0), isbarb(false), pak(pak)
	{}

	std::vector<Ref<Player>> met;

	std::vector<Ref<Unit>> units;
	Ref<Unit> active;

	int  gold;
	bool isbarb;
	bool pak;

	static std::vector<Ref<Player>> All();

};

}  // namespace C35
