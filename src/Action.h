
#pragma once

#include <functional>

#include "Common.h"
#include "Repository.h"

namespace C35
{

struct Action : RepositoryBase<Action>
{
	std::string name;
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

struct Unit;

struct UnitAction
{
	enum { none, movedirect, move, attack, sentry, sleeping, working } action;
	Ref<Unit> unit;
	Pos target;
	Dir6 facing;
};

}  // namespace C35

