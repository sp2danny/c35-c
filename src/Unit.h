
#pragma once

#include "Common.h"

namespace C35
{
struct UnitType
{
	int         utix;
	std::string name;
	enum
	{
		none,
		att,
		off
	} primary;
	struct
	{
		UC a, d, m, h;
	} base;

	static UnitType& lookup(int);
	static int lookup(std::string);

	template<typename... Args>
	static int emplace(Args&&...);

private:
	static std::map<int, UnitType> table;
	static int next;
};

struct Unit
{
	int uix, utix;
	UnitType& base() { return UnitType::lookup(utix); }
	struct
	{
		UC a, d, m, mr, h, hr;
	} stats;
	int xp, lev;
	int x, y;
	Player* owner;

	int fromtype(std::string);

	template<typename... Args>
	static int emplace(Args&&...);

private:
	static std::map<int, Unit> table;
	static int next;
};

template<typename... Args>
int UnitType::emplace(Args&&... args)
{
	auto [iter, ok] = table.emplace(next, UnitType{std::forward<Args>(args)...});
	if (!ok)
		return 0;
	iter->second.utix = next;
	return next++;
}


template<typename... Args>
int Unit::emplace(Args&&... args)
{
	auto [iter, ok] = table.emplace(next, Unit{std::forward<Args>(args)...});
	if (!ok)
		return 0;
	iter->second.uix = next;
	return next++;
}


}  // namespace C35
