
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

void C35::Board::Load(std::istream& in)
{
	ReadBinary(in, w);
	ReadBinary(in, h);
	map.resize(w * h);

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			auto& h = *at(x, y);
			h.clr();
			ReadBinary(in, h.tile);
			ReadBinary(in, h.cover);
			ReadBinary(in, h.mask);
			ReadBinary(in, h.flavor);
			ReadBinary(in, h.resource);
			h.x  = x;
			h.y  = y;
		}
	}
	MapN();
}

void C35::Board::Save(std::ostream& out) const
{
	WriteBinary(out, w);
	WriteBinary(out, h);

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			const auto& h = *at(x, y);
			WriteBinary(out, h.tile);
			WriteBinary(out, h.cover);
			WriteBinary(out, h.mask);
			WriteBinary(out, h.flavor);
			WriteBinary(out, h.resource);
		}
	}
}

void C35::Board::MapN(bool wrap)
{
	auto add_n = [&](C35::HexCore& hex, Dir6 d, int x, int y)
	{
		hex.neigh[d] = nullptr;
		if (y < 0 || y >= h)
			return;
		if (x < 0)
		{
			if (wrap)
				x += w;
			else
				return;
		}
		if (x >= w)
		{
			if (wrap)
				x -= w;
			else
				return;
		}
		hex.neigh[d] = at(x, y);
	};

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			HexCore& h = *at(x, y);

			h.x  = x;
			h.y  = y;
			if (y % 2)
			{
				// odd
				add_n(h, d6_upleft,    x,     y - 1);
				add_n(h, d6_upright,   x + 1, y - 1);
				add_n(h, d6_downleft,  x,     y + 1);
				add_n(h, d6_downright, x + 1, y + 1);
				h.px = SZ + SZ * x;
				h.py = YSZ * y;
			}
			else
			{
				// even
				add_n(h, d6_upleft,    x - 1, y - 1);
				add_n(h, d6_upright,   x,     y - 1);
				add_n(h, d6_downleft,  x - 1, y + 1);
				add_n(h, d6_downright, x,     y + 1);
				h.px = (SZ / 2) + SZ * x;
				h.py = YSZ * y;
			}
			add_n(h, d6_right, x + 1, y);
			add_n(h, d6_left, x - 1, y);
		}
	}
}
