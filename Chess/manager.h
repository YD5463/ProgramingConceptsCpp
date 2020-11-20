#pragma once

#include <iostream>
#include <string>
#include "tool.h"

#include "king.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h"
#include "queen.h"

#include <vector>

#define LEN 64
using namespace std;

class manager
{
public:
	manager(char* board);
	~manager();
	void main_mennege(string msg);
	void print_board();
	char* send_ans();
	char** _board;
protected:
	char* ans;
	int surce1;
	int surce2;
	int dest1;
	int dest2;
	tool*** array_tools;
	tool* get_tool(char type);
	bool is_in_board();
	void split_msg(string msg);
	int is_eat();
	bool right_player();
	bool is_chess_mistake();
	int is_chess_or_mat();
	int curr_player;//white=0
};