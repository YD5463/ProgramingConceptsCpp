#pragma once
#include "Menu.h"
#include <iostream>
#include <string>

#define EXIT 3
#define LEN 100

Menu::Menu() 
{
	_board  = new cimg_library::CImg<unsigned char>(700, 700, 1, 3, 1);
	_disp = new cimg_library::CImgDisplay(*_board, "Super Paint");
	mainMenu();
}

Menu::~Menu()
{
	_disp->close();
	delete _board;
	delete _disp;
}
/*
This function is the menu of the program 
she call to function according to the user input.
*/
void Menu::mainMenu()
{
	Shape* arrayShapes[LEN];
	int choice = 0;
	int len = 0;
	int choice2 = 0;
	int j = 0;
	while (choice != EXIT)
	{
		choice = printMenu();
		switch (choice)
		{
		case 0:
			choice2 = print_shapes_options();
			if (choice2 == 0)
			{
				Shape* s1 = create_c();
				arrayShapes[len++] = s1;
			}
			else if (choice2 == 1)
			{
				Shape* s2 = create_a();
				arrayShapes[len++] = s2;
			}
			else if (choice2 == 2)
			{
				try
				{
					Shape* s3 = create_t();
					arrayShapes[len++] = s3;
				}
				catch (invalid_argument& d)
				{
					cout << d.what() << endl;
				}
			}
			else if (choice2 == 3)
			{
				try
				{
					Shape* s4 = create_r();
					arrayShapes[len++] = s4;
				}
				catch (invalid_argument& d)
				{
					cout << d.what() << endl;
				}
			}
			break;
		case 1:
			len = case_one(arrayShapes, len);
			break;
		case 2:
			delete_array(arrayShapes, len);
			len = 0;
			break;
		case 3:
			delete_array(arrayShapes, len);
			break;
		}
	}
}
/*
This function input the shapes and delete them from the board and from the memory
and return 0 to len of the array.
*/
void Menu::delete_array(Shape** arrayShapes,int len)
{
	int j = 0;
	for (j = 0; j < len; j++)
	{
		arrayShapes[j]->clearDraw(*_disp, *_board);
		delete arrayShapes[j];
	}
}
/*
This function print menu of create shepe and input from the user the choice
and return the choice to the "main".
*/
int Menu::print_shapes_options()
{
	int choice = 0;
	cout << "Enter 0 to add a circle.\nEnter 1 to add an arrow.\nEnter 2 to add a triangle.\nEnter 3 to add a rectangle." << endl;
	cin >> choice;
	system("cls");//clear the cmd
	return choice;
}

/*
This function print the first menu and input the user choice
and return that.
*/
int Menu::printMenu()
{
	int choice = 0;
	cout << "Enter 0 to add a new shape.\nEnter 1 to modify or get information from a current shape.\n";
	cout << "Enter 2 to delete all of the shapes.\nEnter 3 to exit." << endl;
	cin >> choice;
	system("cls");
	return choice;
}
/*
This function iput from the user the ditails to create a new circle,
create the circle and draw it and return the object.
*/
Shape* Menu::create_c()
{
	int r = 0;
	string name;
	double X = 0;
	double Y = 0;
	cout << "Please enter X:" << endl;
	cin >> X;
	cout << "Please enter Y:" << endl;
	cin >> Y;
	cout << "Please enter radius:" << endl;
	cin >> r;
	cout << "Please enter the name of the shape:" << endl;
	getchar();
	std::getline(std::cin, name);
	system("cls");
	Point p(X, Y);
	Shape* s1 = new Circle(p, r, "Circle", name);
	s1->draw(*_disp, *_board);
	return s1;
}
/*
This function iput from the user the ditails to create a new arrow,
create the arrow and draw it and return the object.
*/
Shape * Menu::create_a()
{
	string name;
	double X = 0;
	double Y = 0;
	double X2 = 0;
	double Y2 = 0;
	cout << "Enter the X of point number : 1" << endl;
	cin >> X;
	cout << "Enter the Y of point number: 1" << endl;
	cin >> Y;
	cout << "Enter the X of point number: 2" << endl;
	cin >> X2;
	cout << "Enter the Y of point number: 2" << endl;
	cin >> Y2;
	cout << "Enter the name of the shape:" << endl;
	getchar();
	std::getline(std::cin, name);
	system("cls");
	Point p1(X, Y);
	Point p2(X2, Y2);
	Shape* s2 = new Arrow(p1, p2, "Arrow", name);
	s2->draw(*_disp, *_board);
	return s2;
}
/*
This function iput from the user the ditails to create a new triangle,
triangle the circle and draw it and return the object.
*/
Shape * Menu::create_t()
{
	string name;
	double X = 0;
	double Y = 0;
	double X2 = 0;
	double Y2 = 0;
	double X3 = 0;
	double Y3 = 0;
	cout << "Enter the X of point number : 1" << endl;
	cin >> X;
	cout << "Enter the Y of point number: 1" << endl;
	cin >> Y;
	cout << "Enter the X of point number: 2" << endl;
	cin >> X2;
	cout << "Enter the Y of point number: 2" << endl;
	cin >> Y2;
	cout << "Enter the X of point number: 3" << endl;
	cin >> X3;
	cout << "Enter the Y of point number: 3" << endl;
	cin >> Y3;
	cout << "Enter the name of the shape:" << endl;
	getchar();
	std::getline(std::cin, name);
	system("cls");
	Point p1(X, Y);
	Point p2(X2, Y2);
	Point p3(X3, Y3);
	Shape* s3 = new Triangle(p1, p2, p3, "Triangle", name);
	s3->draw(*_disp, *_board);
	return s3;
}
/*
This function iput from the user the ditails to create a new rectangle,
create the rectangle and draw it and return the object.
*/
Shape* Menu::create_r()
{
	double length = 0;
	double width = 0;
	string name;
	double X = 0;
	double Y = 0;
	cout << "Enter the X of the to left corner:" << endl;
	cin >> X;
	cout << "Enter the Y of the top left corner:" << endl;
	cin >> Y;
	cout << "Please enter the length of the shape:" << endl;
	cin >> length;
	cout << "Please enter the width of the shape:" << endl;
	cin >> width;
	cout << "Enter the name of the shape:" << endl;
	getchar();
	std::getline(std::cin, name);
	system("cls");
	Point p1(X, Y);
	Shape* s4 = new myShapes::Rectangle(p1, length, width, "Rectangle", name);
	s4->draw(*_disp, *_board);
	return s4;
}
/*
This function input from the user choice and move or print details or remov shape
accordin to the user choice and return the len(becuse if she delete shape she change the len)
*/
int Menu::case_one(Shape* arrayShapes[],int len)
{
	int j = 0;
	int index_ob = 0;
	int option = 0;
	int X = 0;
	int Y = 0;
	if (len > 0)
	{
		for (j = 0; j < len; j++)
		{
			cout << "Enter " << j << " for " << arrayShapes[j]->getName() << "(" << arrayShapes[j]->getType() << ")" << endl;
		}
		cin >> index_ob;
		cout << "Enter 0 to move the shape\nEnter 1 to get its details.\nEnter 2 to remove the shape." << endl;
		cin >> option;
		system("cls");
		if (option == 0)
		{
			cout << "Please enter the X moving scale :";
			cin >> X;
			cout << "Please enter the Y moving scale :";
			cin >> Y;
			system("cls");
			Point p_to_move(X, Y);
			arrayShapes[index_ob]->clearDraw(*_disp, *_board);
			arrayShapes[index_ob]->move(p_to_move);
			arrayShapes[index_ob]->draw(*_disp, *_board);
		}
		else if (option == 1)
		{
			arrayShapes[index_ob]->printDetails();
			system("pause");
			system("cls");
		}
		else if (option == 2)
		{
			Shape* temp = arrayShapes[index_ob];
			for (j = index_ob; j < len; j++)
			{
				arrayShapes[j] = arrayShapes[j + 1];
			}
			temp->clearDraw(*_disp, *_board);
			len--;
			delete temp;
		}
	}
	return len;
}
