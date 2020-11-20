#pragma once
#include <iostream>
#include <string>

using namespace std;

class tool
{
public:
	tool(int color);
	tool();
	char get_color();
	virtual bool check_move(int,int,int,int,char**);
protected:
	int _color;
};