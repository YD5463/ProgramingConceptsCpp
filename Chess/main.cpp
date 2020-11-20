#pragma once
#include "manager.h"

void main()
{
	string msg = "a2a3";
	string board = "RNBKQ#NRPPPPPPPPR#######B#######################pppppppprnbkqbnr1";
	manager m(board,msg);
	m.print_board();
	for (int i = 0; i < 10; i++)
	{
		cout << "enter msg:\n";
		cin >> msg;
		m.main_mennege(msg);
		m.print_board();
	}
	system("pause");
}