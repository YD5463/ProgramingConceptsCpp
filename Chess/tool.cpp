#include "tool.h"

tool::tool(int color)
{
	_color = color;
}
tool::tool()
{
}
char tool::get_color()
{
	return _color;
}

bool tool::check_move(int, int, int, int, char **)
{
	return false;
}
