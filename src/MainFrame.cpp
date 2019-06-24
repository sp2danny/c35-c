
#include <iostream>
#include <fstream>
#include <chrono>

#include <alib.hpp>

#include "FrameForwards.h"

#include "Hexagon.h"
#include "Board.h"
#include "Unit.h"
#include "Player.h"
#include "MapGui.h"

namespace C35
{
class MainFrame : public Frame
{
public:
	MainFrame();
	~MainFrame();

	virtual void Display(sf::RenderWindow&) override;
	virtual bool Done() override;
	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;

private:
	bool wantsQuit = false;

	//Board       board;
	int         ox, oy;
	Ref<Player> p1, p2;

	MapGui gui;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP;

	TP t1, t2, t3;

	int   dx = 0, dy = 0;
	float old_fps = 60.0f;
};

MainFrame::MainFrame()
{
	t1 = t2 = t3 = std::chrono::high_resolution_clock::now();

	Board& board = Game();

	board.Randomize(75, 55);
	board.Instance();

	MakeWarr();
	MakeWorker();
	p1         = Player::lookup(Player::create(100, board, true))->ref();
	p1->name() = "Player One";
	p2         = Player::lookup(Player::create(200, board, true))->ref();
	p2->name() = "Player Two";

	Ref<Unit> u;

	u = board.Spawn("Worker", p1, {7, 7});
	board.active = u;
	auto hx = u->at;
	ox = hx->px - WW / 2;
	oy = hx->py - HH / 2;
	u = board.Spawn("Worker", p2, {8, 7});
	u->set("mine", 90);
	u = board.Spawn("Worker", p2, {8, 8});
	u->set("road", 270);
	u = board.Spawn("Warrior", p2, {9, 7});
	u->set("attack");

	Unit::unloadBase();

	gui.Recalc();
}

MainFrame::~MainFrame()
{
	UnitType::clear();
	Unit::clear();
	Unit::clearcache();
	Player::clear();
}

void MainFrame::Display(sf::RenderWindow& rw)
{
	Game().Display(rw, ox, oy);
	gui.SetOfs(ox,oy);
	gui.Display(rw);

	auto dur = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t1).count();
	auto fps = 2000000 / dur;
	old_fps  = 0.99f * old_fps + 0.01f * fps;
	rw.setTitle(std::to_string((int)(old_fps + 0.5)));
}

bool MainFrame::Done()
{
	return wantsQuit;
}

void MainFrame::Update(int ms)
{
	Game().Update();
	gui.Update(ms);
	t1 = t2;
	t2 = t3;
	t3 = std::chrono::high_resolution_clock::now();
	ox += dx;
	oy += dy;
}

bool MainFrame::ParseInput(sf::Event& e)
{
	static struct
	{
		bool dn, up, lf, rg;
	} down = {0, 0, 0, 0};

	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Escape) wantsQuit = true;

		if (e.key.code == sf::Keyboard::Left)  down.lf = true;
		if (e.key.code == sf::Keyboard::Right) down.rg = true;
		if (e.key.code == sf::Keyboard::Up)    down.up = true;
		if (e.key.code == sf::Keyboard::Down)  down.dn = true;
	}

	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Left)  down.lf = false;
		if (e.key.code == sf::Keyboard::Right) down.rg = false;
		if (e.key.code == sf::Keyboard::Up)    down.up = false;
		if (e.key.code == sf::Keyboard::Down)  down.dn = false;
	}

	int s = 3;
	dx = dy = 0;
	if (down.dn) dy += s;
	if (down.up) dy -= s;
	if (down.rg) dx += s;
	if (down.lf) dx -= s;

	gui.ParseInput(e);

	return false;
}

FramePtr MakeMainFrame()
{
	return std::make_shared<MainFrame>();
}

}  // namespace C35
