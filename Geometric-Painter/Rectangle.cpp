#include "Rectangle.h"
#include <exception>


void myShapes::Rectangle::draw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char WHITE[] = { 255, 255, 255 };
	board.draw_rectangle(_points[0].getX(), _points[0].getY(),
		_points[2].getX(), _points[2].getY(), WHITE, 100.0f).display(disp);
}

void myShapes::Rectangle::clearDraw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char BLACK[] = { 0, 0, 0};
	board.draw_rectangle(_points[0].getX(), _points[0].getY(),
		_points[2].getX(), _points[2].getY(), BLACK, 100.0f).display(disp);
}

myShapes::Rectangle::Rectangle(const Point & a, double length, double width, const string & type, const string & name):Polygon(type,name)
{
	if (length > 0 && width > 0)
	{
		_length = length;
		_width = width;
		Point b(a.getX() + length, a.getY());
		Point c(b.getX(), a.getY() + width);
		Point d(a.getX(), c.getY());
		_points.resize(4);
		_points[0] = a;
		_points[1] = b;
		_points[2] = c;
		_points[3] = d;
	}
	else
	{
		throw std::invalid_argument("invalid argument!");
	}
}

myShapes::Rectangle::~Rectangle()
{
}

double myShapes::Rectangle::getArea() const
{
	return (_length * _width);
}

double myShapes::Rectangle::getPerimeter() const
{
	return (2 * _length + 2 * _width);
}
/*
this functuion input a input and add to the points of the Rectangle.
*/
void myShapes::Rectangle::move(const Point & other)
{
	_points[0] += other;
	_points[1] += other;
	_points[2] += other;
	_points[3] += other;
}
