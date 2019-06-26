
#pragma once

#include <functional>
#include <string>

#include <alib.hpp>

#include "Common.h"
#include "Repository.h"

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

