#pragma once

#include "tool.h"

class king : public tool
{
public:
	king(int color);
	virtual bool check_move(int s1,int s2,int d1,int d2, char** board);
};