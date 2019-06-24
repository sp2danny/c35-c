
#pragma once

#include "FrameSystem.h"

namespace C35
{

class Board;

class Minimap : public Frame
{
public:
	Minimap(int, int, Board&);
	~Minimap();

	virtual void Display(sf::RenderWindow&) override;
	virtual bool Done() override;
	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;

	void Recalc();

	std::string Tooltip() const;

private:
	int x, y;
	Board& brd;
};

}  // namespace C35
