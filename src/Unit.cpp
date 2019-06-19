
#include <cassert>

#include "Unit.h"

// ****************
// *** UnitType ***
// ****************




// ************
// *** Unit ***
// ************

auto C35::Unit::fromtype(std::string n) -> int
{
	int utix = UnitType::lookup(n);
	if (!utix)
		return 0;
	UnitType& ut = *UnitType::lookup(utix);
	int uix = create();
	if (!uix)
		return 0;
	Unit& u = *lookup(uix);
	u.ut  = ut.ref();
	u.stats.a = ut.base.a;
	u.stats.d = ut.base.d;
	u.stats.mr = u.stats.m = ut.base.m;
	u.stats.hr = u.stats.h = ut.base.h;
	u.xp = u.lev = 0;
	return uix;
}

void C35::MakeWarr()
{
	int       id = UnitType::create();
	UnitType& ut = *UnitType::lookup(id);

	ut.name()  = "Warrior";
	ut.primary = UnitType::off;
	ut.base    = {1, 1, 3, 3};
}

void C35::MakeWorker()
{
	int       id = UnitType::create();
	UnitType& ut = *UnitType::lookup(id);

	ut.name()  = "Worker";
	ut.primary = UnitType::none;
	ut.base    = {1, 1, 3, 3};
}


