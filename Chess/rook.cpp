#include "rook.h"

rook::rook(int color):tool(color)
{
}

bool rook::check_move(int s1, int s2, int d1, int d2, char** board)
{
	int i = 0;
	bool result = false;
	if ((((s1 + 1 == d1) || (s1 - 1 == d1)) && (s2==d2)) || (((s2 + 1 == d2) || (s2 - 1 == d2)) && (s1==d1)))
	{
		result = true;
	}
	else if (s1 == d1)
	{
		if (s2 < d2)
		{
			for (i = s2+1; i < d2; i++)
			{
				if (board[s1][i] != '#')
				{
					return false;
				}
				else
				{
					result = true;
				}
			}
		}
		else if(s2>d2)
		{
			for (i = s2 - 1; i > d2; i--)
			{
				if (board[s1][i] != '#')
				{
					return false;
				}
				else
				{
					result = true;
				}
			}
		}
	}
	else if (s2 == d2)
	{
		if (s1 < d1)
		{
			for (i = s1 + 1; i < d1; i++)
			{
				if (board[i][s2] != '#')
				{
					return false;
				}
				else
				{
					result = true;
				}
			}
		}
		else if (s1 > d1)
		{
			for (i = s1 - 1; i > d1; i--)
			{
				if (board[i][s2] != '#')
				{
					return false;
				}
				else
				{
					result = true;
				}
			}
		}
	}
	return result;
}