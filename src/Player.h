
#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "Common.h"
#include "Repository.h"

namespace C35
{

struct Player : RepositoryBase<Player>
{

	UC color;

	City* capital;

	Board* game;

	Player(UC col, Board& b, bool pak)
		: color(col), capital(nullptr), game(&b), gold(0), isbarb(false), pak(pak)
	{}

	std::vector<int> met;

	int  gold;
	bool isbarb;
	bool pak;

	static std::vector<int> all();

};

}  // namespace C35
