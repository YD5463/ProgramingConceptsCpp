#pragma once
#include "tool.h"

class pawn : public tool
{
public:
	pawn(int color);
	virtual bool check_move(int s1, int s2, int d1, int d2, char ** board);
	int first_time;
};