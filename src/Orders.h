
#pragma once

#include <vector>

#include "Common.h"

namespace C35
{
struct Order
{
	enum EOrder
	{
		move,
		move1,
		explore,
		road,
		autopilot,
		roadto,
		rail,
		mine,
		irri,
		bridge,
		clear,
		attack,
		fortify,
		wake
	};
	int  action;
	bool WorkerJob() const { return action >= road && action <= clear; }
	int tx, ty;
	int dir;
	int data;

	static Order Move(int x, int y) { return Order{move, x,y, 0,0}; }
	static Order Attack(int x, int y) { return Order{attack, x, y, 0, 0}; }
	static Order Irri() { return Order{irri, 0, 0, 0, 0}; }
};

struct Orders
{
	std::vector<Order> orders;

	Orders& stack(Order o) { orders.push_back(o); return *this; }
	Orders& set(Order o) { orders.clear(); return stack(o); }

};


}  // namespace C35
