
#include <cassert>

#include "Player.h"

auto C35::Player::All()
	-> std::vector<Ref<Player>>
{
	std::vector<Ref<Player>> a;
	a.reserve(tab().size());
	for (auto&& p : tab())
	{
		auto& pp = const_cast<Player&>(p.second);
		a.push_back(pp.ref());
	}
	return a;
}




