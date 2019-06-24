
#include "MapGui.h"

#include <SFML/Graphics/Text.hpp>
#include <alib.hpp>

#include "Unit.h"
#include "Hexagon.h"
#include "Minimap.h"
#include "Board.h"

namespace gui
{
sf::Font   font;
sf::Text   text;
alib::CIS  box, circ;
alib::Refl boxr, circr;
int        bw, bh;
}  // namespace gui

C35::MapGui::MapGui()
	: mm(25, 25)
{
	gui::font.loadFromFile("arial.ttf");
	gui::text = sf::Text(" ", gui::font);
	gui::box.LoadBMP("img/box.bmp", {255, 0, 255}, 0, 0);
	gui::box.Instance(0);
	gui::boxr = gui::box.Refl(0);
	gui::bw   = gui::box.Width();
	gui::bh   = gui::box.Height();
	gui::boxr.setPosition((float)WW - gui::bw, (float)HH - gui::bh);
	gui::box.UnloadBase();

	gui::circ.LoadBMP("img/circ_g.bmp", {255, 0, 255}, 33, 21);
	gui::circ.Instance(0);
	gui::circr = gui::circ.Refl(0);
}

void C35::MapGui::Display(sf::RenderWindow& rw)
{
	rw.draw(gui::boxr);
	Board& brd = Game();
	if (brd.active)
	{
		gui::text.setString(brd.active->name());
		gui::text.setCharacterSize(18);
		gui::text.setStyle(sf::Text::Bold);
		gui::text.setFillColor(sf::Color::Black);
		auto bnds = gui::text.getLocalBounds();
		int  tw   = (int)bnds.width;

		gui::text.setPosition(WW - gui::bw + gui::bw / 2.0f - tw / 2.0f, HH - gui::bh + 12.0f);

		auto hex = brd.active->at;
		if (hex)
		{
			sf::Vector2f pos((float)hex->px - ox, (float)hex->py - oy);
			gui::circr.setPosition(pos);
			rw.draw(gui::circr);

			auto r = brd.active->refl;
			r.setPosition(pos);
			rw.draw(r);
		}
		rw.draw(gui::text);
	}
	mm.Display(rw);
}

bool C35::MapGui::ParseInput(sf::Event&)
{
	return false;
}

void C35::MapGui::Update(int) {}

bool C35::MapGui::Done()
{
	return false;
}
