
#pragma once

#include <functional>
#include <string>

#include <alib.hpp>

#include "Common.h"
#include "Repository.h"
#include "FrameSystem.h"

namespace C35
{

struct Action : RepositoryBase<Action>, DisplayObject
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

	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;
	virtual void Display(sf::RenderWindow&) override;
	virtual bool Done() override;

	alib::Refl refl;

	static void AllOff();
};

struct Unit;

struct UnitAction
{
	enum { none, movedirect, move, attack, sentry, sleeping, working } action;
	Ref<Unit> unit;
	Pos target;
	Dir6 facing;
};

void MakeActions();

}  // namespace C35

