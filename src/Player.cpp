
#include <cassert>

#include "Player.h"

int C35::Player::nextId = 1;
std::map<int, C35::Player> C35::Player::players;

auto C35::Player::newPlayer() -> int
{
	players.try_emplace(nextId);
	return nextId++;
}

auto C35::Player::lookup(int id) -> Player*
{
	auto iter = players.find(id);
	if (iter == players.end())
		return nullptr;
	return &iter->second;
}

int C35::Player::lookup(std::string name)
{
	for (auto&& p : players)
	{
		if (p.second.name == name)
			return p.first;
	}
	return 0;
}

std::vector<int> C35::Player::all()
{
	std::vector<int> a;
	a.reserve(players.size());
	for (auto&& p : players)
	{
		a.push_back(p.first);
	}
	return a;
}




