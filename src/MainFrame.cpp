
#include <iostream>
#include <fstream>

#include <alib.hpp>

#include "FrameForwards.h"

#include "Hexagon.h"
#include "Board.h"
#include "Unit.h"
#include "Player.h"

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
	// alib::AC worker_ac, settler_ac, warrior_ac, horseman_ac;
	bool wantsQuit = false;

	// alib::Refl worker, settler, warrior, horseman;

	Board board;
	int   ox, oy;
	Ref<Player> p1, p2;
};

MainFrame::MainFrame()
{
	board.Randomize(300, 200);
	board.Instance();
	ox = oy = 0;
	MakeWarr(); MakeWorker();
	p1 = Player::lookup(Player::create(100, board, true))->ref();
	p1->name() = "Player One";
	p2 = Player::lookup(Player::create(200, board, true))->ref();
	p2->name() = "Player Two";

	board.spawn("Worker",  p1, {7, 7});
	board.spawn("Worker",  p2, {8, 7});
	board.spawn("Worker",  p2, {8, 7});
	board.spawn("Warrior", p2, {9, 7});
}

void MainFrame::Display(sf::RenderWindow& rw)
{
	board.Display(rw, ox, oy);
}

bool MainFrame::Done()
{
	return wantsQuit;
}

void MainFrame::Update(int)
{
	board.update();
}

bool MainFrame::ParseInput(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Escape)
			wantsQuit = true;
		if (e.key.code == sf::Keyboard::Left)
			ox -= 3;
		if (e.key.code == sf::Keyboard::Right)
			ox += 3;
		if (e.key.code == sf::Keyboard::Up)
			oy -= 3;
		if (e.key.code == sf::Keyboard::Down)
			oy += 3;
	}
	return false;
}

FramePtr MakeMainFrame()
{
	return std::make_shared<MainFrame>();
}

}  // namespace C35
