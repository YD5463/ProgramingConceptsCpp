#pragma once
#include "tool.h"

class bishop : public tool
{
public:
	bishop(int color);
	virtual bool check_move(int s1, int s2, int d1, int d2, char** board);
};
