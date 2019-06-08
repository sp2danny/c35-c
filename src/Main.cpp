
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <alib.hpp>

#include "Common.h"
#include "FrameSystem.h"
#include "FrameForwards.h"

namespace C35 { struct Intro; }

struct C35::Intro : C35::Frame
{
	Intro();
	virtual void Display(sf::RenderWindow&) override;
	virtual bool Done() override;
	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;
private:
	alib::CIS back_cis;
	alib::AC horsie_ac;
	alib::Refl horsie, back;
	bool wantquit = false;
};

C35::Intro::Intro()
{
	back_cis.Load("img/back.bmp");
	back_cis.Instance(0);
	back = back_cis.Refl(0);
	back.setPosition(0,0);
	horsie_ac.Load("img/walk.ad");
	horsie_ac.Instance(90);
	horsie = horsie_ac.Refl("run", 90+45, rand()%256);
	horsie.setPosition({500,350});
}

void C35::Intro::Display(sf::RenderWindow& window)
{
	window.draw(back);
	window.draw(horsie);
}

bool C35::Intro::Done() { return wantquit;}

void C35::Intro::Update(int)
{
	horsie.Update();
}

bool C35::Intro::ParseInput(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		/**/ if (e.key.code == sf::Keyboard::Escape)
			wantquit = true;
		else if (e.key.code == sf::Keyboard::Space)
			Push(MakeMainFrame());
	}
	return false;
}

void Main(const C35::StrVec& args)
{
	(void)args;

	srand((unsigned int)time(0));
	
	const auto& vms = sf::VideoMode::getFullscreenModes();
	
	bool found = false;
	long long pixcnt;
	sf::VideoMode vm;
	
	for (const auto& x : vms)
	{
		if ((x.width >= 640) && (x.height >= 480) && x.bitsPerPixel >= 24)
		{
			if (!found)
			{
				vm = x;
				found = true;
				pixcnt = x.width * x.height;
			}
			else
			{
				long long pc = x.width * x.height;
				if (pc < pixcnt)
				{
					pixcnt = pc;
					vm = x;
				}
			}
		}
	}
	
	if (!found) return;
	
	#ifndef NDEBUG
	sf::RenderWindow window(vm, "C35");
	#else
	sf::RenderWindow window(vm, "C35", sf::Style::Fullscreen);
	#endif

	C35::Frame::Init("");
	C35::Frame::Push(std::make_shared<C35::Intro>());
	
	C35::Frame::Run(window);

	std::cout << "\ndone.\n";
}

C35::StrVec split(const std::string& s, char delim)
{
	C35::StrVec       result;
	std::stringstream ss{s};
	std::string       item;

	while (std::getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return result;
}

#ifndef CONSOLE
int __cdecl WinMain(void*, void*, char* cargs, int)
{
	Main(split(cargs, ' '));
	return 0;
}
#else
int main(int argc, char* argv[])
{
	C35::StrVec args;
	for (int i = 1; i < argc; ++i)
		args.push_back(argv[i]);
	Main(args);
}
#endif
