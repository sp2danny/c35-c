
#include <cassert>

#include "Unit.h"
#include "Player.h"

// ****************
// *** UnitType ***
// ****************

// ************
// *** Unit ***
// ************

auto C35::Unit::fromtype(std::string_view n) -> int
{
	int utix = UnitType::lookup(n);
	if (!utix) return 0;
	UnitType& ut  = *UnitType::lookup(utix);
	int uix = create();
	if (!uix) return 0;
	Unit& u    = *lookup(uix);
	u.ut       = ut.ref();
	u.stats.a  = ut.base.a;
	u.stats.d  = ut.base.d;
	u.stats.mr = u.stats.m = ut.base.m;
	u.stats.hr = u.stats.h = ut.base.h;
	u.xp = u.lev = 0;
	u.currently.facing = d6_downleft;
	u.currently.unit = Ref<Unit>(uix);
	u.currently.action = UnitAction::none;
	return uix;
}

void C35::Unit::unloadBase(std::string un)
{
	if (un.empty())
	{
		for (auto&& ac : cache)
			ac.second.UnloadBase();
	}
	else
	{
		for (auto&& ac : cache)
			if (ac.first==un)
				ac.second.UnloadBase();
	}
}

void C35::Unit::instance(UC col, std::string_view anim)
{
	std::string name = ut->name();
	auto        iter = cache.find(name);
	if (iter == cache.end())
	{
		iter = cache.try_emplace(name).first;
		iter->second.Load("img/units/" + name + ".fzac");
		auto fort = iter->second.Have("fortify");
		if (fort)
		{
			int i, n = fort->Count();
			for (i = 0; i < n; ++i)
			{
				auto& var  = fort->Get(i);
				auto  dirs = var.AllDirs();
				for (auto d : dirs)
				{
					auto& ba = var.Get(d);
					ba.SetRep(false);
				}
			}
		}
	}
	iter->second.Instance(col);
	refl = iter->second.Refl(std::string(anim), 225, col);
}

void C35::Unit::set(std::string_view anim, short dir)
{
	std::string name = ut->name();
	auto        iter = cache.find(name);
	assert(iter != cache.end());

	refl = iter->second.Refl(std::string(anim), dir, owner ? owner->color : 0);
}

void C35::MakeWarrior()
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
	ut.base    = {0, 0, 3, 0};
}

void C35::MakeSettler()
{
	int       id = UnitType::create();
	UnitType& ut = *UnitType::lookup(id);

	ut.name()  = "Settler";
	ut.primary = UnitType::none;
	ut.base    = {0, 0, 3, 0};
}

void C35::MakePikeman()
{
	int       id = UnitType::create();
	UnitType& ut = *UnitType::lookup(id);

	ut.name()  = "Pikeman";
	ut.primary = UnitType::def;
	ut.base    = {1, 3, 3, 3};
}

void C35::MakeHorseman()
{
	int       id = UnitType::create();
	UnitType& ut = *UnitType::lookup(id);

	ut.name()  = "Horseman";
	ut.primary = UnitType::off;
	ut.base    = {2, 1, 6, 3};
}

