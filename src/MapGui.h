
#pragma once

#include <functional>

#include <alib.hpp>

#include "Common.h"
#include "Repository.h"
#include "FrameSystem.h"

namespace C35
{
	struct Action : RepositoryBase<Action>
	{
		bool haveButton;
		bool haveShortcut;
		bool dynamicLocation;
		bool visible;
		bool enabled;
		int location;
		int x,y;
		alib::AD button;
		std::string tooltip;
		char shortcut;
		std::function<void(Ref<Action>)> onActivate;
	};

	struct MapGui : public Frame
	{
		virtual void Display(sf::RenderWindow&) override;
		virtual bool ParseInput(sf::Event&) override;
		virtual void Update(int) override;
		virtual bool Done() override;


		std::vector<Ref<Action>> actionGroupSystem;
		std::vector<Ref<Action>> actionGroupMap;
		std::vector<Ref<Action>> actionGroupUnit;

		Ref<Unit> active;
	};


}  // namespace C35

