
#include "MapGui.h"

#include <SFML/Graphics/Text.hpp>
#include <alib.hpp>

#include "Unit.h"
#include "Hexagon.h"
#include "Minimap.h"
#include "Board.h"

struct C35::MapGui::Data
{
	sf::Font   font;
	sf::Text   text;
	alib::CIS  box, circ;
	alib::Refl boxr, circr;
	int        bw, bh;
};

C35::MapGui::~MapGui() = default;

C35::MapGui::MapGui()
	: mm(25, 25)
{
	gui = std::make_unique<Data>();

	gui->font.loadFromFile("arial.ttf");
	gui->text = sf::Text(" ", gui->font);
	gui->box.LoadBMP("img/uib.bmp", {255, 0, 255}, 0, 0);
	gui->box.Instance(0);
	gui->boxr = gui->box.Refl(0);
	gui->bw   = gui->box.Width();
	gui->bh   = gui->box.Height();
	gui->boxr.setPosition((float)WW - gui->bw, (float)HH - gui->bh);
	gui->box.UnloadBase();

	gui->circ.LoadBMP("img/circ_g.bmp", {255, 0, 255}, 33, 21);
	gui->circ.Instance(0);
	gui->circr = gui->circ.Refl(0);

	show.minimap = enabled.minimap = true;
	show.unitaction = enabled.unitaction = true;
}

void C35::MapGui::Display(sf::RenderWindow& rw)
{
	rw.draw(gui->boxr);
	Board& brd = Game();
	if (brd.Active())
	{
		gui->text.setString(brd.Active()->name());
		gui->text.setCharacterSize(18);
		gui->text.setStyle(sf::Text::Bold);
		gui->text.setFillColor(sf::Color::Black);
		auto bnds = gui->text.getLocalBounds();
		int  tw   = (int)bnds.width;

		gui->text.setPosition(WW - gui->bw + gui->bw / 2.0f - tw / 2.0f, HH - gui->bh + 12.0f);

		auto hex = brd.Active()->at;
		if (hex)
		{
			sf::Vector2f pos((float)hex->px - brd.ox, (float)hex->py - brd.oy);
			gui->circr.setPosition(pos);
			rw.draw(gui->circr);

			auto r = brd.Active()->refl;
			r.setPosition(pos);
			rw.draw(r);
		}
		rw.draw(gui->text);

		int n = 0;
		for (auto&& a : brd.Active()->ut->available)
		{
			auto r = a->button.Refl(0, 0);
			r.setPosition(a->x, a->y);
			rw.draw(r);
		}

	}
	if (show.minimap)
		mm.Display(rw);
}

bool C35::MapGui::ParseInput(sf::Event& e)
{
	auto& b = Game();

	if (e.type == sf::Event::MouseMoved)
	{
		auto hx = b.Pix(e.mouseMove.x + b.ox, e.mouseMove.y + b.oy);
		b.mouseover = hx;
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
			if (b.mouseover)
				b.mouseover->mask ^= road;
	}

	if (b.Active() && enabled.unitaction)
	{
		int n = 0;
		for (auto&& a : b.Active()->ut->available)
		{
			//a->button.
		}

	}
	if (enabled.minimap)
		mm.ParseInput(e);
	return false;
}

void C35::MapGui::Update(int ms)
{
	if (enabled.minimap)
		mm.Update(ms);
}

bool C35::MapGui::Done()
{
	return false;
}
