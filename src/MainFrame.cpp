
#include <alib.hpp>

#include "FrameForwards.h"

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
	alib::AC worker_ac, settler_ac, warrior_ac, horseman_ac;
	bool wantsQuit = false;
	
	alib::Refl worker, settler, warrior, horseman;
};

MainFrame::MainFrame()
{
	UC mycol = 97;
	
	#define LD(x) \
		x ## _ac.Load( "./img/units/" #x ".ac"); \
		x ## _ac.Instance(mycol); \
		x = x ## _ac.Refl("idle", 180, mycol)

	LD(worker);
	LD(settler);
	LD(warrior);
	LD(horseman);
	
	worker.setPosition(100,100);
	settler.setPosition(100,200);
	warrior.setPosition(200,100);
	horseman.setPosition(200,200);

}

void MainFrame::Display(sf::RenderWindow& rw)
{
	rw.draw(worker);
	rw.draw(settler);
	rw.draw(warrior);
	rw.draw(horseman);
}

bool MainFrame::Done()
{
	return wantsQuit;
}

void MainFrame::Update(int)
{
	worker   .Update();
	settler  .Update();
	warrior  .Update();
	horseman .Update();
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