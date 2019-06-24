
#pragma once

#include <functional>

#include <alib.hpp>

#include "Common.h"
#include "Repository.h"
#include "FrameSystem.h"
#include "Minimap.h"

namespace C35
{
struct Action : RepositoryBase<Action>
{
	bool        haveButton;
	bool        haveShortcut;
	bool        dynamicLocation;
	bool        visible;
	bool        enabled;
	int         location;
	int         x, y;
	alib::AD    button;
	std::string tooltip;
	char        shortcut;

	std::function<void(Ref<Action>)> onActivate;
};

struct MapGui : public Frame
{
	MapGui(Board&);

	virtual void Display(sf::RenderWindow&) override;
	virtual bool ParseInput(sf::Event&) override;
	virtual void Update(int) override;
	virtual bool Done() override;

	struct
	{
		bool minimap, advisors, replay, unitaction, diplomacy, portrait;
	} show, enabled;

	std::vector<Ref<Action>> actionGroupSystem;
	std::vector<Ref<Action>> actionGroupMap;
	std::vector<Ref<Action>> actionGroupUnit;

	Ref<Player> pak;

	void Recalc() { mm.Recalc(); }

	void SetOfs(int x, int y) { ox=x; oy=y; }

private:
	alib::BA minimap, portrait;
	alib::AC advisors, replay, diplomacy;
	Board& brd;
	Minimap mm;
	int ox,oy;
};

}  // namespace C35
