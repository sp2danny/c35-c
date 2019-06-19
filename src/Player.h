
#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "Common.h"

namespace C35
{
struct Player;
typedef std::reference_wrapper<Player> PRef;

struct Player
{
	int id;

	std::string name;
	UC color;

	City* capital;

	Board* game;

	std::vector<int> met;

	int  gold;
	bool isbarb;
	bool pak;

	static int newPlayer();
	static Player* lookup(int);
	static int lookup(std::string);

	static std::vector<int> all();

private:
	static int nextId;
	static std::map<int, Player> players;
};

}  // namespace C35
