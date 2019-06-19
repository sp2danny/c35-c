
#pragma once

#include "Common.h"
#include "Repository.h"

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

	static int fromtype(std::string_view);

	void instance(UC) {}

};

extern void MakeWarr(), MakeWorker();

}  // namespace C35
