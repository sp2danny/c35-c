
#pragma once

#include <alib.hpp>

#include "Common.h"
#include "Hexagon.h"
#include "Repository.h"

namespace C35
{
class Board
{
public:
	int w, h;
	int ox=0, oy=0;

	std::vector<HexCore> map;

	HexCore*       at(int, int);
	const HexCore* at(int x, int y) const { return ((Board*)this)->at(x, y); }
	HexCore*       Pix(int, int);

	void Randomize(int, int);
	void Load(std::istream&);
	void Save(std::ostream&) const;

	void Instance();
	void Display(sf::RenderWindow&);

	Ref<Unit> Spawn(std::string_view, Ref<Player>, Pos);

	void Update(int);

	Ref<Unit> active;
	HexCore* mouseover;

private:
	void MapN(bool = true);

	alib::AD tiles;
	alib::CIS mo;
	alib::AD roads;
};

Board& Game();

}  // namespace C35
