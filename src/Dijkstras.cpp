
#include "Dijkstras.h"

namespace {

	struct H {
		int cost;
		H* neigh[6];
		C35::HexCore* orig;
	};

	std::vector<H> map;
	std::vector<H*> cand;
	std::vector<H*> found;
}

void C35::prepare_dijkstras(const HexCore& from)
{
	map.clear(); cand.clear(); found.clear();
	Board& b = Game();
	map.reserve(b.map.size());
	for (auto& hx : b.map)
	{
		H h { -1, {0,0,0,0,0}, &hx };
		map.push_back(h);
		if (&hx == &from)
		{
			map.back().cost = 0;
			found.push_back(&map.back());
		}
	}
}

int C35::linear_distance([[maybe_unused]] const HexCore& to)
{
	return 0;
}


int C35::travel_cost([[maybe_unused]] const HexCore& to)
{
	return 0;
}



