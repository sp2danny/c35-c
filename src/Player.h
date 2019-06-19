
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

	std::vector<int> met;

	int  gold;
	bool isbarb;
	bool pak;

	static std::vector<int> all();

};

}  // namespace C35
