
#pragma once

#include "Board.h"

namespace C35
{

void prepare_dijkstras(const HexCore& from);

int linear_distance(const HexCore& to);

int travel_cost(const HexCore& to);

}

