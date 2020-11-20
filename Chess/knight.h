#pragma once
#include "tool.h"

class knight : public tool
{
public:
	knight(int color);
	virtual bool check_move(int s1,int s2,int d1,int d2,char** board);
};