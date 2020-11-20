#include "king.h"

king::king(int color):tool(color)
{
}

bool king::check_move(int s1, int s2, int d1, int d2,char** board)
{
	return (abs(d1 - s1) <= 1 && abs(d2 - s2) <= 1);
}
