
#pragma once

#include "Common.h"
#include "Hexagon.h"

namespace C35
{

	class Board
	{
	public:
		int w, h;
		std::vector<HexCore> map;

		HexCore* at(int, int);
		const HexCore* at(int x, int y) const { return ((Board*)this)->at(x,y); }
		HexCore* pix(int, int);

		void Randomize(int, int);
		void Load(std::istream&);
		void Save(std::ostream&) const;

	private:
		void MapN(bool = true);
	};











}

