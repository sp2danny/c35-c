
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
		HexCore* pix(int, int);

		void Randomize(int, int);
		void Load(std::istream&);
		void Save(std::ostream&);

	private:
		void MapN();
	};











}

