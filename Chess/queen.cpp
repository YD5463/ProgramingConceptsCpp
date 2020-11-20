#include "queen.h"
#include "rook.h"
#include "bishop.h"
queen::queen(int color):tool(color)
{
}
bool queen::check_move(int s1, int s2, int d1, int d2, char ** board)
{
	rook r(_color);
	bishop b(_color);
	return (r.check_move(s1, s2, d1, d2, board) || b.check_move(s1, s2, d1, d2, board));
}
