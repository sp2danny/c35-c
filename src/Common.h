
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdint>
#include <memory>
#include <cstddef>

using namespace std::literals;

namespace C35
{
	inline const int SZ = 60;
	inline const int YSZ = 47;
	inline int WW;
	inline int HH;
	inline const int MRG = 60;

	extern float offs_x, offs_y;

	typedef std::vector<std::string> StrVec;
	typedef std::vector<int> IdList;

	struct Pos { int x, y; Pos() : x(0), y(0) {} Pos(int x, int y) : x(x), y(y) {} };

	enum Dir6 : int { d6_beg=0, d6_upright=d6_beg, d6_right, d6_downright, d6_downleft, d6_left, d6_upleft, d6_end };

	const short Degree[d6_end] { 60, 0, 300, 240, 180, 120 };

	inline Dir6 operator++(Dir6& d) { return d = (Dir6)((int)d + 1); }
	inline Dir6 operator--(Dir6& d) { return d = (Dir6)((int)d - 1);}

	inline Dir6 CW  (Dir6 d) { return (Dir6)(((int)d + 1) % 6); }
	inline Dir6 CCW (Dir6 d) { return (Dir6)(((int)d + 5) % 6); }

	struct Hexagon;
	struct HexCore;

	struct Player;
	struct Unit;
	struct City;

	typedef unsigned char UC;
}

template<typename T>
int ssize(const T& t)
{ return (int)std::size(t); }

template<typename T>
void ReadBinary(std::istream& istr, T& val)
{ istr.read((char*)&val, sizeof(val)); }

template<typename T>
void WriteBinary(std::ostream& ostr, const T& val)
{ ostr.write((char*)&val, sizeof(val)); }

