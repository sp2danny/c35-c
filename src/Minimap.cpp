
#include "Minimap.h"

#include <alib.hpp>

#include "Board.h"

struct C35::Minimap::Data
{
	alib::Refl r_g, r_s, r_c, r_d, r_m, r_n, r_o, r_p, r_r;
	alib::CIS  c_g, c_s, c_c, c_d, c_m, c_n, c_o, c_p, c_r;
};

C35::Minimap::Minimap(int x, int y)
	: x(x), y(y)
{
	data = std::make_unique<Data>();

	alib::RGB purpl{255, 0, 255};

#define LD(x)                                                          \
	data->c_##x.LoadBMP("img/MiniMap/mmm_" #x ".bmp", purpl, 0, 0);    \
	data->r_##x = data->c_##x.Refl(0)

	LD(g); LD(s); LD(c);
	LD(d); LD(m); LD(n);
	LD(o); LD(p); LD(r);

#undef LD
}

void C35::Minimap::Recalc()
{
	Board&      brd   = Game();
	static bool first = true;
	if (first)
	{
		pw    = 4 * brd.w + 2;
		ph    = 3 * brd.h;
		tex.create(pw, ph);
		first = false;
	}

	for (int y = 0; y < brd.h; ++y)
	{
		for (int x = 0; x < brd.w; ++x)
		{
			float xx  = 4.0f * x + ((y % 2) ? 2.0f : 0.0f);
			float yy  = 3.0f * y;
			auto  hex = brd.At(x, y);

			switch (hex->tile)
			{
			case grass:
			// case bonus:
			case hill:
				data->r_g.setPosition({xx, yy});
				tex.draw(data->r_g);
				break;
			case plains:
				data->r_p.setPosition({xx, yy});
				tex.draw(data->r_p);
				break;
			// case desert:
			// case floodp:
			// case tundra:
			//	mm_d.Overlay(minimap, xx, yy);
			//	break;
			// case mount:
			//	mm_m.Overlay(minimap, xx, yy);
			//	break;
			case coast:
			case sea:
				// case ocean:
				data->r_s.setPosition({xx, yy});
				tex.draw(data->r_s);
				break;
			}
		}
	}
	tex.display();
}

C35::Minimap::~Minimap() = default;

namespace {
typedef std::vector<sf::Vertex> VxVec;

void icls(sf::RenderWindow& rw, VxVec& line)
{
	line.push_back(line.front());
	rw.draw(line.data(), line.size(), sf::LineStrip);
}

template<typename... Args>
void icls(sf::RenderWindow& rw, VxVec& line, int x, int y, Args... args)
{
	line.push_back(sf::Vector2f((float)x, (float)y));
	icls(rw, line, args...);
}

template<typename... Args>
void cls(sf::RenderWindow& rw, Args... args) // closed line strip
{
	VxVec line;
	line.reserve(sizeof...(args)+1);
	icls(rw, line, args...);
}
}  // namespace

void C35::Minimap::Display(sf::RenderWindow& rw)
{
	sf::Sprite sprite(tex.getTexture());
	sprite.setPosition((float)x, (float)y);
	rw.draw(sprite);

	auto& m  = Game();
	auto  hx = m.At(m.w - 1, m.h - 1);
	int   ww = hx->px + SZ;
	int   hh = hx->py + YSZ;

	int x1, x2, y1, y2;
	x1 = x + m.ox * pw / ww;
	x2 = x1 + WW * pw / ww;
	y1 = y + m.oy * ph / hh;
	y2 = y1 + HH * ph / hh;

	cls(rw, x1,y1, x2,y1, x2,y2, x1,y2);
}

bool C35::Minimap::Done()
{
	return false;
}

void C35::Minimap::Update([[maybe_unused]] int ms)
{
	//
}

bool C35::Minimap::ParseInput(sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		mx = e.mouseMove.x;
		my = e.mouseMove.y;
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		auto& m  = Game();
		auto  hx = m.At(m.w - 1, m.h - 1);
		int   ww = hx->px + SZ;
		int   hh = hx->py + YSZ;
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			int xx = mx-x, yy = my-y;
			if (xx>0 && xx<pw && yy>0 && yy<ph)
			{
				m.ox = (xx * ww / pw) - (WW / 2);
				m.oy = (yy * hh / ph) - (HH / 2);
			}
		}
	}
	return false;
}

std::string C35::Minimap::Tooltip() const
{
	return ""s;
}

