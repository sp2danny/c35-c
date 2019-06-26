
#include <cassert>
#include <cmath>

#include "Board.h"
#include "Player.h"

auto C35::Game() -> Board&
{
	static Board board;
	return board;
}

auto C35::Board::at(int x, int y) -> HexCore*
{
	int idx = y * w + x;
	assert((idx >= 0) && (idx < ssize(map)));
	return map.data() + idx;
}

auto C35::Board::Pix(int px, int py) -> HexCore*
{
	HexCore* bsf = nullptr;
	float    dst = 0.0f;
	for (auto&& h : map)
	{
		float d = (float)std::hypot(py - h.py, px - h.px);
		if (!bsf || d < dst)
		{
			bsf = &h;
			dst = d;
			continue;
		}
	}
	if (dst < 25.0f)
		return bsf;
	else
		return nullptr;
}

void C35::Board::Update(int ms)
{
	for (auto&& hx : map)
	{
		hx.Update(ms);
	}
}

void C35::Board::Randomize(int ww, int hh)
{
	w = ww;
	h = hh;
	map.resize(w * h);

	auto dfe = [ww, hh](int x, int y) -> int {
		int xd, yd;
		if (x > (ww / 2))
			xd = (ww - 1) - x;
		else
			xd = x;
		if (y > (hh / 2))
			yd = (hh - 1) - y;
		else
			yd = y;
		return std::min(xd, yd);
	};

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			auto& h = *at(x, y);
			h.Clr();
			h.x = x; h.y = y;
			auto d = dfe(h.x, h.y);
			if (d < 3)
			{
				h.tile = sea;
				continue;
			}
			if (d < 5)
			{
				h.tile = coast;
				continue;
			}
			auto r = rand() % 100;
			if (r < 40)
				h.tile = grass;
			else if (r < 80)
				h.tile = plains;
			else
				h.tile = hill;
		}
	}

	MapN();
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
			h.Clr();
			ReadBinary(in, h.tile);
			ReadBinary(in, h.cover);
			ReadBinary(in, h.mask);
			ReadBinary(in, h.flavor);
			ReadBinary(in, h.resource);
			h.x = x;
			h.y = y;
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
	auto add_n = [&](C35::HexCore& hex, Dir6 d, int x, int y) {
		hex.neigh[d] = nullptr;
		if (y < 0 || y >= h) return;
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

			h.x = x;
			h.y = y;
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
			add_n(h, d6_left,  x - 1, y);
		}
	}
}

void C35::Board::Instance()
{
	tiles.Load("img/tiles.ad");
	tiles.Instance(0);
	mo.LoadBMP("img/circ_b.bmp", {255,0,255}, 32,42);
	mo.Instance(0);
	roads.Load("img/roads.ad");
	roads.Instance(0);
}

void C35::Board::Display(sf::RenderWindow& rw)
{
	for (int y = 0; y < h; ++y)
	{
		int yy = at(0, y)->py - oy;
		if (yy < -MRG) continue;
		if (yy > (HH + MRG)) break;
		for (int x = 0; x < w; ++x)
		{
			HexCore& hx = *at(x, y);
			int      xx = hx.px - ox;
			if (xx < -MRG) continue;
			if (xx > (WW + MRG)) break;
			alib::Refl refl = tiles.Refl(hx.tile, 0);
			refl.setPosition((float)xx, (float)yy);
			rw.draw(refl);
			if (mouseover == &hx)
			{
				alib::Refl refl = mo.Refl(0);
				refl.setPosition((float)xx, (float)yy);
				rw.draw(refl);
			}
			if (hx.mask & road)
			{
				short r = 0;
				for (Dir6 d = d6_beg; d != d6_end; ++d)
				{
					auto n = hx.neigh[d];
					if (!n) continue;
					if (n->mask & road)
						r |= 1 << d;
				}
				assert(r>=0 && r<64);
				alib::Refl refl = roads.Refl(r, 0);
				refl.setPosition((float)xx-32, (float)yy-32);
				rw.draw(refl);
			}
		}
	}

	for (int y = 0; y < h; ++y)
	{
		int yy = at(0, y)->py - oy;
		if (yy < -MRG) continue;
		if (yy > (HH + MRG)) break;
		for (int x = 0; x < w; ++x)
		{
			if (active && x == active->x && y == active->y) continue;
			HexCore& hx = *at(x, y);
			if (hx.units.empty()) continue;
			int xx = hx.px - ox;
			if (xx < -MRG) continue;
			if (xx > (WW + MRG)) break;
			auto r = hx.units.back()->refl;
			r.setPosition((float)xx, (float)yy);
			rw.draw(r);
		}
	}
}

auto C35::Board::Spawn(std::string_view type, Ref<Player> player, Pos pos) -> Ref<Unit>
{
	int       id   = Unit::fromtype(type);
	Unit&     unit = *Unit::lookup(id);
	HexCore*  hx   = at(pos.x, pos.y);
	Ref<Unit> ref  = unit.ref();

	unit.x     = pos.x;
	unit.y     = pos.y;
	unit.owner = player;
	unit.at    = hx;

	std::string name = player->name();
	name += "'s ";
	name += type;
	unit.name() = name;

	unit.instance(player->color);
	hx->units.push_back(ref);

	return ref;
}
