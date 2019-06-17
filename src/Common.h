
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdint>
#include <memory>
#include <cstddef>

namespace C35
{
	extern const int SZ, YSZ;
	extern float offs_x, offs_y;

	typedef std::vector<std::string> StrVec;
	typedef std::vector<int> IdList;

	struct Pos { int x, y; Pos() : x(0), y(0) {} Pos(int x, int y) : x(x), y(y) {} };

	enum Dir6 : int { d6_beg=0, d6_upright=d6_beg, d6_right, d6_downright, d6_downleft, d6_left, d6_upleft, d6_end };

	const short Degree[d6_end] { 60, 0, 300, 240, 180, 120 };

	inline Dir6 operator++(Dir6& d) { return d = (Dir6)(1+(int)d); }

	inline Dir6 CW  (Dir6 d) { return (Dir6) ( ((int)d + 1) % 6); }
	inline Dir6 CCW (Dir6 d) { return (Dir6) ( ((int)d + 5) % 6); }

	struct Hexagon;
	struct Player;
	class  Board;
	class  PlayerBoard;
	struct Orders;
	struct Unit;
	struct City;
	class  UI;
	struct City;
	struct PlayerHex;
	struct Movement;
	class  GameEngine;
	//class  ControllerAPI;
	//class  Controller;

	typedef unsigned char UC;

}

inline std::string IntToStr(int i) { return std::to_string(i); }
inline std::string IntToStrPad(int i, unsigned n, char p) { std::string s = std::to_string(i); while(s.length()<n) s=p+s; return s; }

template<typename T>
std::ptrdiff_t ssize(const T& t)
{ return (std::ptrdiff_t)std::size(t); }

template<typename T>
void ReadBinary(std::istream& istr, T& val)
{
	istr.read((char*)&val, sizeof(val));

	/*int i,n = sizeof(T);
	char* p = (char*) &val;

	for (i=0; i<n; ++i)
	{
		char c;
		istr.read(&c,1);
		(*p) = c;
		++p;
	}*/
}

template<typename T>
void WriteBinary(std::ostream& ostr, const T& val)
{
	int i, n = sizeof(T);
	const char* p = (char*) &val;

	for (i=0; i<n; ++i)
	{
		char c;
		c = (*p);
		++p;
		ostr.write(&c,1);
	}
}
