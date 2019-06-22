
#include "MapGui.h"

#include <SFML/Graphics/Text.hpp>
#include <alib.hpp>

#include "Unit.h"

namespace gui
{
sf::Font   font;
sf::Text   text;
alib::CIS  box;
alib::Refl boxr;
int        bw, bh;
} // namespace gui

C35::MapGui::MapGui()
{
	gui::font.loadFromFile("arial.ttf");
	gui::text = sf::Text(" ", gui::font);
	gui::box.LoadBMP("img/box.bmp", {255, 0, 255}, 0, 0);
	gui::box.Instance(0);
	gui::boxr = gui::box.Refl(0);
	gui::bw   = gui::box.Width();
	gui::bh   = gui::box.Height();
	gui::boxr.setPosition(640.0f - gui::bw, 480.0f - gui::bh);
}

void C35::MapGui::Display(sf::RenderWindow& rw)
{
	rw.draw(gui::boxr);
	if (active)
	{
		gui::text.setString(active->name());
		gui::text.setCharacterSize(18);
		gui::text.setStyle(sf::Text::Bold);
		gui::text.setFillColor(sf::Color::Black);
		auto bnds = gui::text.getLocalBounds();
		int  tw   = (int)bnds.width;

		gui::text.setPosition(640.0f - gui::bw + gui::bw / 2.0f - tw / 2.0f, 480.0f - gui::bh + 12.0f);

		rw.draw(gui::text);
	}
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
