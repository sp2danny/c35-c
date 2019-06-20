
#pragma once

#include "Common.h"
#include "Repository.h"

#include "alib.hpp"

namespace C35
{

struct UnitType : RepositoryBase<UnitType>
{

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

};

struct HexCore;

struct Unit : RepositoryBase<Unit>
{
	Ref<UnitType> ut;

	UnitType& base() { return *ut; }
	struct
	{
		UC a, d, m, mr, h, hr;
	} stats;
	int xp, lev;
	int x, y;

	Player* owner;
	HexCore* at;

	static int fromtype(std::string_view);

	void instance(UC, std::string_view = "idle");
	void set(std::string_view, short=225);

	alib::Refl refl;
	static void clearcache() {cache.clear();}

	static void unloadBase(std::string = "");

private:
	inline static std::map<std::string, alib::AC> cache;
};

extern void MakeWarr(), MakeWorker();

}  // namespace C35
