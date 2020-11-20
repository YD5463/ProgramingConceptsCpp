#pragma once
#include "Shape.h"
#include "Circle.h"
#include "Arrow.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "CImg.h"
#include <vector>
#include <iostream>
#include <sstream>


class Menu
{
public:

	Menu();
	~Menu();
	// more functions..

private: 
	void mainMenu();
	void delete_array(Shape** arrayShapes, int len);
	int print_shapes_options();
	int printMenu();
	Shape* create_c();
	Shape* create_a();
	Shape* create_t();
	Shape* create_r();
	int case_one(Shape* arrayShapes[], int len);
	cimg_library::CImg<unsigned char>* _board;
	cimg_library::CImgDisplay* _disp;
};

