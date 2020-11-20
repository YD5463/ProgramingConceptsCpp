#pragma once
#include "tool.h"

class queen : public tool
{
public:
	queen(int color);
	virtual bool check_move(int s1, int s2, int d1, int d2, char** board);
};