
#pragma once

#include <iostream>
#include <vector>
#include <set>

#include "Common.h"
#include "Unit.h"

namespace C35
{

typedef unsigned short USh;

// masks
const USh road = 1;

const USh river_upright   = 64;
const USh river_right     = 128;
const USh river_downright = 256;

// cover
const USh  forest = 1;
const USh  jungle = 2;
const USh  mine   = 3;
const USh  irri   = 4;

// tiles
const USh grass  = 1;
const USh plains = 3;
const USh hill   = 7;
const USh coast  = 9;
const USh sea    = 10;


struct Hexagon;

struct HexCore
{
	USh     tile, cover, mask;
	UC      flavor;
	int     x, y;
	int     px, py;
	UC      resource;

	Player* owner;
	City*   city;

	bool Roaded() const;
	bool IsLand() const;
	bool IsSea() const;
	bool IsRivered(Dir6) const;
	bool HaveCover() const;

	std::vector<Ref<Unit>> units;

	void update();

	void clr()
	{
		tile = cover = mask = 0;
		flavor = resource = 0;
		owner  = nullptr;
		city   = nullptr;
	}

	HexCore* neigh[d6_end];

private:
};


}  // namespace C35