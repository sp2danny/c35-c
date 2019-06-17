
#include <cassert>

#include "Unit.h"

// ****************
// *** UnitType ***
// ****************

auto C35::UnitType::lookup(int i) -> UnitType&
{
	assert(table.count(i));
	return table[i];
}

auto C35::UnitType::lookup(std::string name) -> int
{
	for (auto&& u : table)
	{
		if (u.second.name == name)
			return u.first;
	}
	return 0;
}

std::map<int, C35::UnitType> C35::UnitType::table;

int C35::UnitType::next = 1;

// ************
// *** Unit ***
// ************

auto C35::Unit::fromtype(std::string n) -> int
{
	int utix = UnitType::lookup(n);
	if (!utix)
		return 0;
	UnitType& ut = UnitType::lookup(utix);
	int uix = emplace();
	if (!uix)
		return 0;
	Unit& u = table[uix];
	u.utix  = utix;
	u.stats.a = ut.base.a;
	u.stats.d = ut.base.d;
	u.stats.mr = u.stats.m = ut.base.m;
	u.stats.hr = u.stats.h = ut.base.h;
	u.xp = u.lev = 0;
	return uix;
}

std::map<int, C35::Unit> C35::Unit::table;

int C35::Unit::next = 1;

namespace C35
{
extern void MakeWarr(), MakeWorker();
}


void C35::MakeWarr()
{
	int       id = UnitType::emplace();
	UnitType& ut = UnitType::lookup(id);

	ut.name    = "Warrior";
	ut.primary = UnitType::off;
	ut.base    = {1, 1, 3, 3};
}

void C35::MakeWorker()
{
	int       id = UnitType::emplace();
	UnitType& ut = UnitType::lookup(id);

	ut.name    = "Worker";
	ut.primary = UnitType::none;
	ut.base    = {1, 1, 3, 3};
}


