
#pragma once

#include <alib.hpp>

#include "Common.h"
#include "Hexagon.h"

namespace C35
{

class Board
{
public:
	int w, h;
	std::vector<HexCore> map;

	HexCore* at(int, int);
	const HexCore* at(int x, int y) const { return ((Board*)this)->at(x,y); }
	HexCore* pix(int, int);

	void Randomize(int, int);
	void Load(std::istream&);
	void Save(std::ostream&) const;

	void Instance();
	void Display(sf::RenderWindow&, int, int);

	Ref<Unit> spawn(std::string_view, Ref<Player>, Pos);

	void update();

private:
	void MapN(bool = true);

	alib::AD tiles;
};

}

