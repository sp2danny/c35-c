
#include <cassert>
#include <utility>

// --------------------------------------------

#include "FrameSystem.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

std::vector<C35::FramePtr>  C35::Frame::stack;
std::vector<C35::UpdatePtr> C35::Frame::actives;
std::vector<C35::InputPtr>  C35::Frame::listeners;

C35::FramePtr C35::Frame::modal  = nullptr;
C35::FramePtr C35::Frame::system = nullptr;

std::string C35::Frame::title;

void C35::Frame::Init(std::string name)
{
	title = name;
	stack.clear();
	listeners.clear();
	actives.clear();
	modal  = nullptr;
	system = nullptr;
}

void C35::Frame::AddListener(InputPtr it)
{
	listeners.push_back(std::move(it));
}

void C35::Frame::AddActive(UpdatePtr ut)
{
	actives.push_back(std::move(ut));
}

void C35::Frame::AddSubFrame(FramePtr sub)
{
	subFrames.push_back(sub);
}

void C35::Frame::Run(sf::RenderWindow& window)
{
	window.setTitle(title);

	sf::Event lst_mm_e;

	lst_mm_e.type = sf::Event::MouseMoved;
	lst_mm_e.mouseMove.x = lst_mm_e.mouseMove.y = 0;

	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	sf::Clock clock;

	auto last = clock.getElapsedTime().asMilliseconds();

	Frame* old = nullptr;

	while (true)
	{
		if (!window.isOpen())
			break;
		if (stack.empty())
			break;

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (e.type == sf::Event::MouseMoved)
				lst_mm_e = e;

			if (modal)
				modal->ParseInput(e);
			else
				stack.back()->ParseInput(e);
			if (system)
				system->ParseInput(e);
			for (auto&& it : listeners)
				it->ParseInput(e);
		}

		// --- Update ---
		auto now  = clock.getElapsedTime().asMilliseconds();
		auto ticks = now - last;
		if (old != &*stack.back())
		{
			ticks = 0;
			old   = &*stack.back();
		}
		stack.back()->Update(ticks);
		if (modal)
			modal->Update(ticks);
		if (system)
			system->Update(ticks);
		for (auto&& ut : actives)
			ut->Update(ticks);
		last = now;

		// --- Display ---
		window.clear();
		stack.back()->Display(window);
		if (modal)
			modal->Display(window);
		if (system)
			system->Display(window);
		window.display();

		// --- Frame Phase ---
		if (system && system->Done())
			return;
		if (!window.isOpen())
			return;
		if (modal)
		{
			if (modal->Done())
				modal = nullptr;
		} else {
			if (stack.back()->Done())
			{
				stack.pop_back();
				if (!stack.empty())
					stack.back()->ParseInput(lst_mm_e);
			}
		}
		for (auto iter = listeners.begin(); iter != listeners.end();)
		{
			if ((*iter)->Done())
				iter = listeners.erase(iter);
			else
				++iter;
		}
		for (auto iter = actives.begin(); iter != actives.end();)
		{
			if ((*iter)->Done())
				iter = actives.erase(iter);
			else
				++iter;
		}
	}
}

void C35::Frame::PushUnder(FramePtr f)
{
	assert(!stack.empty());
	auto itr = stack.end();
	stack.insert(--itr, std::move(f));
}

void C35::Frame::Push(FramePtr f)
{
	stack.push_back(std::move(f));
}

void C35::Frame::Replace(FramePtr f)
{
	stack.back() = std::move(f);
}

void C35::Frame::Modal(FramePtr m)
{
	modal = std::move(m);
}

void C35::Frame::System(FramePtr s)
{
	system = std::move(s);
}

