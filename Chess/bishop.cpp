#include "bishop.h"

bishop::bishop(int color) :tool()
{
}

bool bishop::check_move(int s1, int s2, int d1, int d2, char** board)
{
	bool ans = false;
	int one1 = 0;
	int one2 = 0;
	if ((s1 - 1 == d1 && s2 - 1 == d2) || (s1 - 1 == d1 && s2 + 1 == d2) || (s1 + 1 == d1 && s2 - 1 == d2) || (s1 + 1 == d1 && s2 + 1 == d2))
	{
		return true;
	}
	else if (s1 > d1 && s2 > d2)
	{
		one1 = -1;
		one2 = -1;
	}
	else if (s1 > d1 && s2 < d2)
	{
		one1 = -1;
		one2 = 1;
	}
	else if (s1 < d1 && s2 < d2)
	{
		one1 = 1;
		one2 = 1;
	}
	else if (s1<d1 && s2>d2)
	{
		one1 = 1;
		one2 = -1;
	}
	else
	{
		return false;
	}
	while (s1 != d1 - one1 || s2 != d2 - one2)
	{
		s1+=one1;
		s2+=one2;
		if (board[s1][s2] != '#')
		{
			return false;
		}
		else
		{
			ans = true;
		}
	}
	return ans;
}

