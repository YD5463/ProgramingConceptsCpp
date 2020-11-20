#include "Triangle.h"


void Triangle::draw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char GREEN[] = { 0, 255, 0 };
	board.draw_triangle(_points[0].getX(), _points[0].getY(),
		_points[1].getX(), _points[1].getY(),
		_points[2].getX(), _points[2].getY(), GREEN, 100.0f).display(disp);
}

void Triangle::clearDraw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char BLACK[] = { 0, 0, 0 };
	board.draw_triangle(_points[0].getX(), _points[0].getY(),
		_points[1].getX(), _points[1].getY(),
		_points[2].getX(), _points[2].getY(), BLACK, 100.0f).display(disp);
}
/*
constractor of Triangle
check if the three points equl in x or y if yes she throw eroor
else she init new Triangle.
*/
Triangle::Triangle(const Point & a, const Point & b, const Point & c, const string & type, const string & name) :Polygon(type, name)
{
	if (!((a.getY()==b.getY() && b.getY()==c.getY()) || (a.getX()==b.getX() && b.getX()==c.getX())))
	{
		_points.resize(3);
		_points[0] = a;
		_points[1] = b;
		_points[2] = c;
	}
	else
	{
		throw invalid_argument("invalid argument!");
	}
}

Triangle::~Triangle()
{
}
/*
This function calc the area and reurn it.
*/
double Triangle::getArea() const
{
	double dArea = ((_points[1].getX() - _points[0].getX())*(_points[2].getY() - _points[0].getY()) - (_points[2].getX() - _points[0].getX())*(_points[1].getY() -_points[0].getY())) / 2.0;
	return (dArea >= 0.0) ? dArea : -dArea;
}
/*
this function get the parts lenght by the distance between the pointer and return the result.
*/
double Triangle::getPerimeter() const
{
	double ab = _points[0].distance(_points[1]);
	double ac = _points[0].distance(_points[2]);
	double bc = _points[1].distance(_points[2]);
	return ab + ac + bc;
}
/*
this functuion input a input and add to the points of the Triangle.
*/
void Triangle::move(const Point & other)
{
	_points[0] += other;
	_points[1] += other;
	_points[2] += other;
}
