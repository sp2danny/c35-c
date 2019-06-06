
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define SFML_STATIC

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Common.h"
#include "FrameSystem.h"
#include "Anim.h"

namespace C35 { struct Intro; }

struct C35::Intro : C35::Frame
{
	Intro();
	virtual void Display() override;
	virtual bool Done() override;
	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;
private:
	//Anim::CIS back;
	//Anim::AC horsie_ac;
	//Anim::Refl horsie;
};

C35::Intro::Intro()
{
	//back.LoadExt("back.bmp");
	//horsie_ac.LoadExt("knight.ac");
	//horsie_ac.Instance(90);
	//horsie = horsie_ac.Refl("run", 90, 180);
}

void C35::Intro::Display() {}
bool C35::Intro::Done() { return false;}
void C35::Intro::Update(int) {}
bool C35::Intro::ParseInput(sf::Event&) {return false;}


void Main([[maybe_unused]] const C35::StrVec& args)
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "C35");

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
