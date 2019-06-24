
// --------------------------------------------

#include "Hexagon.h"

// ***************
// *** HexCore ***
// ***************

bool C35::HexCore::Roaded() const
{
	return city || (mask & road);
}

bool C35::HexCore::IsLand() const
{
	if (city)
		return true;
	switch (tile)
	{
	case sea:
	case coast:
		return false;
	default:
		return true;
	}
}

bool C35::HexCore::IsSea() const
{
	if (city)
		return true;
	switch (tile)
	{
	case coast:
	case sea:
		return true;
	default:
		return false;
	}
}

bool C35::HexCore::IsRivered(Dir6 d) const 
{
	HexCore* n;
	switch (d)
	{
	case d6_upright:
		return mask & river_upright;
	case d6_right:
		return mask & river_right;
	case d6_downright:
		return mask & river_downright;
	case d6_downleft:
		n = neigh[d];
		return n && (n->mask & river_upright);
	case d6_left:
		n = neigh[d];
		return n && (n->mask & river_right);
	case d6_upleft:
		n = neigh[d];
		return n && (n->mask & d6_downright);
	default:
		return false;
	}
}

bool C35::HexCore::HaveCover() const
{
	return cover != 0;
}

void C35::HexCore::Update()
{
	for (auto&& u : units)
	{
		u->refl.Update();
	}
}

