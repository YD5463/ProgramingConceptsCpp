#pragma once
#include "tool.h"

class rook : public tool
{
public:
	rook(int color);
	virtual bool check_move(int s1,int s2,int d1,int d2, char** board);
};