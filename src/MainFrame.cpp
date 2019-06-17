
#include <iostream>
#include <fstream>

#include <alib.hpp>

#include "FrameForwards.h"

#include "Hexagon.h"

namespace C35
{

class MainFrame : public Frame
{
public:
	MainFrame();

	virtual void Display(sf::RenderWindow&) override;
	virtual bool Done() override;
	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;

private:
	//alib::AC worker_ac, settler_ac, warrior_ac, horseman_ac;
	bool wantsQuit = false;
	
	//alib::Refl worker, settler, warrior, horseman;

	//Board board;
};

MainFrame::MainFrame()
{


}

void MainFrame::Display(sf::RenderWindow& rw)
{

}

bool MainFrame::Done()
{
	return wantsQuit;
}

void MainFrame::Update(int)
{

}

bool MainFrame::ParseInput(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Escape)
			wantsQuit = true;
	}
	return false;
}

FramePtr MakeMainFrame()
{
	return std::make_shared<MainFrame>();
}


}  // namespace C35

