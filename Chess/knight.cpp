#include "knight.h"

knight::knight(int color):tool(color)
{
}

bool knight::check_move(int s1, int s2, int d1, int d2, char ** board)
{
	return ((abs(d1 - s1) == 2 && abs(d2 - s2) == 1) || (abs(d2 - s2) == 2 && abs(d1 - s1) == 1));
}
