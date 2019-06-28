
#pragma once

#include <optional>

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

	HexCore*       At(int, int);
	const HexCore* At(int x, int y) const { return ((Board*)this)->At(x, y); }
	HexCore*       Pix(int, int);

	void Randomize(int, int);
	void Load(std::istream&);
	void Save(std::ostream&) const;

	void Instance();
	void Display(sf::RenderWindow&);

	Ref<Unit> Spawn(std::string_view, Ref<Player>, Pos);

	void Update(int);

	void Activate(Ref<Unit>);
	Ref<Unit> Active();

	HexCore* mouseover;
	std::optional<alib::Refl> mor;

private:
	Ref<Unit> active;

	void MapN(bool = true);

	alib::AD tiles;
	alib::CIS mo;
	alib::AD roads;
};

Board& Game();

}  // namespace C35
