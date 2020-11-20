#include "pawn.h"

pawn::pawn(int color):tool(color),first_time(1)
{
}

bool pawn::check_move(int s1, int s2, int d1, int d2, char ** board)
{
	int one = -1;
	if (board[s1][s2] >= 'a' && board[s1][s2] <= 'z')
	{
		one = 1;
	}
	if (first_time)
	{
		if (s1 + (2 * one) == d1 && s2 == d2)
		{
			if (board[s1 + one][s2] == '#' && board[s1 + (2*one)][s2]=='#')
			{
				return true;
			}
		}
	}
	if (board[d1][d2] != '#')
	{
		if (s1 + one == d1 && abs(d2 - s2) == 1)
		{
			return true;
		}
	}
	return (s1 + one == d1 && s2 == d2);
}
