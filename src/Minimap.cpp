
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

	alib::RGB purpl {255,0,255};

	#define LD(x)                                \
		data->c_##x.LoadBMP("img/MiniMap/mmm_"   \
		#x ".bmp", purpl, 0, 0);                 \
		data->r_##x = data->c_##x.Refl(0);

	LD(g); LD(s); LD(c);
	LD(d); LD(m); LD(n);
	LD(o); LD(p); LD(r);

	#undef LD

}

void C35::Minimap::Recalc()
{
	Board& brd = Game();
	static bool first = true;
	if (first) {
		tex.create(4*brd.w+2, 3*brd.h);
		first = false;
	}

	for (int y = 0; y < brd.h; ++y)
	{
		for (int x = 0; x < brd.w; ++x)
		{
			float xx  = 4.0f * x + ((y % 2) ? 2.0f : 0.0f);
			float yy  = 3.0f * y;
			auto  hex = brd.at(x, y);

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


void C35::Minimap::Display(sf::RenderWindow& rw)
{
	sf::Sprite sprite(tex.getTexture());
	sprite.setPosition((float)x,(float)y);
	rw.draw(sprite);
}

bool C35::Minimap::Done() { return false; }

void C35::Minimap::Update(int) {}

bool C35::Minimap::ParseInput(sf::Event&) { return false; }

std::string C35::Minimap::Tooltip() const
{
	return ""s;
}




