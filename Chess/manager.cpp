#include "manager.h"
#include "pawn.h"
#define ROW 8
/*
constractor that init the board in char and the board in tool in the board game
and the curr player.
*/
manager::manager(char* board)
{
	int count = 0;
	int i, j;
	_board = new char *[ROW];
	for (i = 0; i < ROW; i++)
	{
		_board[i] = new char[ROW];
	}
	for (i=0;i<ROW;i++)
	{
		for (j = 0; j < ROW; j++)
		{
			_board[i][j] = board[count++];
		}
	}
	array_tools = new tool**[ROW];
	for (int i = 0; i < ROW; ++i)
	{
		array_tools[i] = new tool*[ROW];
		for (int j = 0; j < ROW; ++j)
		{
			array_tools[i][j] = new tool();
		}
	}
	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			array_tools[i][j] = get_tool(_board[i][j]);
		}
	}
	ans = new char[1];
	print_board();
	curr_player = board[64]-48;
}
/*
This function print the board in chars.
*/
void manager::print_board()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			cout << _board[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
/*
This function check teh color of the tool and the typr and crate
and new object by that and return him
*/
tool* manager::get_tool(char type)
{
	int color = 2;
	if (type >= 'a' && type <= 'z')
	{
		color = 0;
	}
	else if (type >= 'A' && type <= 'Z')
	{
		color = 1;
	}
	else
	{
		return 0;
	}
	tool* t = 0;
	if (tolower(type) == 'k')
	{
		t = new king(color);
	}
	else if (tolower(type) == 'q')
	{
		t = new queen(color);
	}
	else if (tolower(type) =='b')
	{
		t = new bishop(color);
	}
	else if (tolower(type)=='r')
	{
		t = new rook(color);
	}
	else if (tolower(type) == 'n')
	{
		t = new knight(color);
	}
	else if (tolower(type) == 'p')
	{
		t = new pawn(color);
	}
	return t;
}
/*
destractor that delete the array tools(board in object) and the board(board in chars)
*/
manager::~manager()
{
	for (int i = 0; i < ROW; i++)
	{
		delete _board[i];
	}
	delete _board;
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			delete array_tools[i][j];
		}
		delete array_tools[i];
	}
	delete array_tools;
}
/*
input the msg(for exmple:a2a4)
This function call to checkes and change the answer and the board by them.
*/
void manager::main_mennege(string msg)
{
	split_msg(msg);
	ans = "7";
	if (surce1 != dest1 || surce2 != dest2)
	{
		ans = "5";
		if (is_in_board())
		{
			ans = "2";
			if (right_player())
			{
				ans = "3";
				if (is_eat() != -1)
				{
					ans = "5";
					if (array_tools[surce1][surce2])
					{
						ans = "6";
						if (array_tools[surce1][surce2]->check_move(surce1, surce2, dest1, dest2, _board))
						{
							tool* tempt = array_tools[dest1][dest2];
							char tempc = _board[dest1][dest2];
							_board[dest1][dest2] = _board[surce1][surce2];
							_board[surce1][surce2] = '#';
							array_tools[dest1][dest2] = array_tools[surce1][surce2];
							array_tools[surce1][surce2] = 0;
							if (is_chess_mistake())
							{
								ans = "4";
								_board[surce1][surce2] = _board[dest1][dest2];
								_board[dest1][dest2] = tempc;
								array_tools[surce1][surce2] = array_tools[dest1][dest2];
								array_tools[dest1][dest2] = tempt;
							}
							else
							{
								ans = "0";
								if (is_chess_or_mat()==1)
								{
									ans = "1";
								}
								else if (is_chess_or_mat() == -1)
								{
									ans = "8";
								}
								if (curr_player == 0)
								{
									curr_player = 1;
								}
								else
								{
									curr_player = 0;
								}
								if (tolower(_board[dest1][dest2]) == 'p')
								{
									((pawn*)(array_tools[dest1][dest2]))->first_time = 0;
								}
							}
						}
					}
				}
			}
		}
	}
}
/*
This function check if the index in surce and in the dest in valid indexs
and return true or false
*/
bool manager::is_in_board()
{
	return ((surce1 < 8 && surce1 >= 0) && (surce2 < 8 && surce2 >= 0) && (dest1 < 8 && dest1 >= 0) && (dest2 < 8 && dest2 >= 0));
}

char* manager::send_ans()
{
	return ans;
}
/*
This function get the msg for exmple a2a4 and convert the msg to indexs
*/
void manager::split_msg(string msg)
{
	string part1 = msg.substr(0, 2);
	string part2 = msg.substr(2, 2);
	string temp;
	temp = part1.substr(0, 1);
	surce2 = temp[0] - 'a';
	temp = part1.substr(1, 1);
	surce1 = temp[0] - 49;
	surce1 = (surce1 - 7)*-1;
	temp = part2.substr(0, 1);
	dest2 = temp[0] - 'a';
	temp = part2.substr(1, 1);
	dest1 = temp[0] - 49;
	dest1 = (dest1- 7)*-1;
}
/*
This function check if in the dest have a enemy tool or frindely tool or nothing
and return -1 if  frindely tool is in the dest index, 1 if enemy tool and 0 if nothing 
*/
int manager::is_eat()
{
	int result = 0;
	int one = 1;
	if ((curr_player && _board[dest1][dest2]>='a' && _board[dest1][dest2]<='z') || (!curr_player && _board[dest1][dest2] >= 'A' && _board[dest1][dest2] <= 'Z')&& _board[dest1][dest2] != '#')
	{
		result = -1;
	}
	else if (_board[dest1][dest2]!='#')
	{
		result = 1;
	}
	return result;
}
/*
This function check if the tool who moved is the tool of the player that his turn.
return 1 of it's ok and 0 if not
*/
bool manager::right_player()
{
	return ((curr_player && _board[surce1][surce2] <= 'z' && _board[surce1][surce2]>='a') || (!curr_player && _board[surce1][surce2] <= 'Z' && _board[surce1][surce2]>='A'));
}
/*
This function find the king of the player that his turn and check if any tool of the player that
not his turn if one of them(the tools) can moved to the index of the king
and if he can moved the func return 1
*/
bool manager::is_chess_mistake()
{
	int i = 0;
	int j = 0;
	int k1 = 0;
	int k2 = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			if (_board[i][j] == 'k' && curr_player == 1)
			{
				k1 = i;
				k2 = j;
				break;
			}
			else if (_board[i][j] == 'K' && curr_player == 0)
			{
				k1 = i;
				k2 = j;
				break;
			}
		}
	}
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			if (_board[i][j] <= 'z' && _board[i][j]>='a' && curr_player == 0)
			{
				if (array_tools[i][j]->check_move(i, j, k1, k2, _board))
				{
					return true;
				}
			}
			else if (_board[i][j] <= 'Z' && _board[i][j] >= 'A' && curr_player == 1)
			{
				if (array_tools[i][j]->check_move(i, j, k1, k2, _board))
				{
					return true;
				}
			}
		}
	}
	return false;
}
/*
This function check if any tool of the player that his turn can moved to the enemy king
and return 1 if it's chess,0 if not chess and -1 if it's mat
*/
int manager::is_chess_or_mat()
{
	int i;
	int j;
	int k1 = 0;
	int k2 = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			if (_board[i][j] == 'k' && curr_player==0)
			{
				k1 = i;
				k2 = j;
				break;
			}
			else if (_board[i][j] == 'K' && curr_player == 1)
			{
				k1 = i;
				k2 = j;
				break;
			}
		}
	}
	if (array_tools[dest1][dest2]->check_move(dest1, dest2, k1, k2, _board))
	{
		return 1;
	}
	return 0;
}
