
#include <iostream>
#include <fstream>
#include <chrono>

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
	~MainFrame();

	virtual void Display(sf::RenderWindow&) override;
	virtual bool Done() override;
	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;

private:
	bool wantsQuit = false;

	alib::CIS  box;
	alib::Refl boxr;

	Board       board;
	int         ox, oy;
	Ref<Player> p1, p2;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP;
	TP                                                                  t1, t2, t3;

	int   dx = 0, dy = 0;
	float old_fps = 60.0f;
};

MainFrame::MainFrame()
{
	t1 = t2 = t3 = std::chrono::high_resolution_clock::now();

	board.Randomize(300, 200);
	board.Instance();

	MakeWarr();
	MakeWorker();
	p1         = Player::lookup(Player::create(100, board, true))->ref();
	p1->name() = "Player One";
	p2         = Player::lookup(Player::create(200, board, true))->ref();
	p2->name() = "Player Two";

	Ref<Unit> u;

	u = board.spawn("Worker", p1, {7, 7});
	auto hx = u->at;
	ox = hx->px - 640 / 2;
	oy = hx->py - 480 / 2;
	u = board.spawn("Worker", p2, {8, 7});
	u->set("mine", 90);
	u = board.spawn("Worker", p2, {8, 8});
	u->set("road", 270);
	u = board.spawn("Warrior", p2, {9, 7});
	u->set("attack");

	Unit::unloadBase();

	box.LoadBMP("img/box.bmp", {255, 0, 255}, 0, 0);
	box.Instance(0);
	boxr = box.Refl(0);
	boxr.setPosition(640.0f - box.Width(), 480.0f - box.Height());
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
	board.Display(rw, ox, oy);
	rw.draw(boxr);
	auto dur = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t1).count();
	auto fps = 2000000 / dur;
	old_fps  = 0.99f * old_fps + 0.01f * fps;
	rw.setTitle(std::to_string((int)(old_fps + 0.5)));
}

bool MainFrame::Done()
{
	return wantsQuit;
}

void MainFrame::Update(int)
{
	board.update();
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

	int s = 1;
	dx = dy = 0;
	if (down.dn) dy += s;
	if (down.up) dy -= s;
	if (down.rg) dx += s;
	if (down.lf) dx -= s;

	return false;
}

FramePtr MakeMainFrame()
{
	return std::make_shared<MainFrame>();
}

}  // namespace C35
