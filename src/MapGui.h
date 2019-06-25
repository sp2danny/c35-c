
#pragma once

#include <alib.hpp>

#include "Common.h"
#include "Repository.h"
#include "FrameSystem.h"
#include "Minimap.h"
#include "Action.h"

namespace C35
{

struct MapGui : public Frame
{
	MapGui();
	~MapGui();

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

private:
	alib::BA minimap, portrait;
	alib::AC advisors, replay, diplomacy;
	Minimap mm;

	struct Data;
	std::unique_ptr<Data> gui;
};

}  // namespace C35
