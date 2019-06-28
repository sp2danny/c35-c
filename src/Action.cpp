
#include "Action.h"

//	std::string name;
//	bool        haveButton;
//	bool        haveShortcut;
//	bool        dynamicLocation;
//	bool        visible;
//	bool        enabled;
//	int         location;
//	int         x, y;
//	alib::AD    button;
//	std::string tooltip;
//	char        shortcut;
//	std::function<void(Ref<Action>)> onActivate;

namespace C35 {
void RunAction(Ref<Action> a)
{
	std::cout << a->name() << std::endl;
}

void C35::Action::AllOff()
{
	for (auto itr = Action::begin(); itr != Action::end(); ++itr)
	{
		itr->visible = false;
		itr->enabled = false;
	}
}

void C35::Action::Update(int)
{
	refl.setPosition({(float)x, (float)y});
}

bool C35::Action::ParseInput(sf::Event& e)
{
	if (!enabled) return false;
	sf::FloatRect fr;
	refl.getTransform().transformRect(fr);

	auto inside = [](auto p, auto r) -> bool
	{
		if (p.x < r.left) return false;
		if (p.x > (r.left+r.width)) return false;
		if (p.y < r.top) return false;
		if (p.y > (r.top+r.height)) return false;
		return true;
	};

	if (e.type == sf::Event::MouseMoved)
	{
		if (inside(e.mouseMove, fr)) {
			refl = button.Refl(1, 0);
			return true;
		} else {
			refl = button.Refl(0, 0);
		}
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (inside(e.mouseButton, fr))
		{
			onActivate(this->ref());
			return true;
		}
	}
	return false;
}

void C35::Action::Display(sf::RenderWindow& rw)
{
	if (visible)
	{
		rw.draw(refl);
	}
}

bool C35::Action::Done()
{
	return false;
}


void AddAction(alib::AC& ua, std::string name, std::string anim, std::string tt, int location, char shortcut)
{
	int id = Action::create();
	Action& a = *Action::lookup(id);
	a.name() = name;
	a.haveButton = true;
	a.haveShortcut = true;
	a.dynamicLocation = true;
	a.location = location;
	a.x = a.y = 0;
	a.button.AddDir(0, ua.Get(anim).Get(0).Get(0));
	a.button.AddDir(1, ua.Get(anim+"HL").Get(0).Get(0));
	a.button.Instance(0);
	a.tooltip = tt;
	a.shortcut = shortcut;
	a.onActivate = &RunAction;
}

}

void C35::MakeActions()
{
	alib::AC ua;
	ua.Load("img/ActionBtn.ac");

	AddAction(ua, "goto", "Goto", "Goto location", 3, 'g');
	AddAction(ua, "fortify", "Fortify", "Dig in for improved defense", 3, 'f');

}


