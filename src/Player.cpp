
#include <cassert>

#include "Player.h"



std::vector<int> C35::Player::all()
{
	std::vector<int> a;
	a.reserve(tab().size());
	for (auto&& p : tab())
	{
		a.push_back(p.first);
	}
	return a;
}




