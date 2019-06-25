
#pragma once

#include "FrameSystem.h"

#include <SFML/Graphics.hpp>

namespace C35
{

class Board;

class Minimap : public Frame
{
public:
	Minimap(int, int);
	~Minimap();

	virtual void Display(sf::RenderWindow&) override;
	virtual bool Done() override;
	virtual void Update(int) override;
	virtual bool ParseInput(sf::Event&) override;

	void Recalc();

	std::string Tooltip() const;

private:
	struct Data;
	std::unique_ptr<Data> data;

	int x, y;
	sf::RenderTexture tex;
};

}  // namespace C35
