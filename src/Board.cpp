
#include <cassert>

#include "Board.h"


auto C35::Board::at(int x, int y) -> HexCore*
{
	int idx = y * w + x;
	assert((idx >= 0) && (idx < ssize(map)));
	return map.data() + idx;
}

auto C35::Board::pix(int px, int py) -> HexCore*
{
	return nullptr;
}

void C35::Board::Randomize(int ww, int hh)
{
	w = ww;
	h = hh;
	map.resize(w * h);

	for (auto&& h : map)
	{
		h.clr();

	}
}


void C35::Board::Load(std::istream&) {}
void C35::Board::Save(std::ostream&) {}





