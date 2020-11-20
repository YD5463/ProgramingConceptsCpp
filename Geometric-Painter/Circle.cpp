#include "Circle.h"
//constractor
Circle::Circle(const Point & center, double radius, const string & type, const string & name):Shape(name, type),_radius(radius),_center(center)
{
}

Circle::~Circle()
{
}
//return the point of the circle center
const Point & Circle::getCenter() const
{
	return _center;
}
//return the radius of the circle
double Circle::getRadius() const
{
	return _radius;
}
//calc and return the area of the circle
double Circle::getArea() const
{
	return PI*_radius*_radius;
}
//calc and return the perimeter of the circle
double Circle::getPerimeter() const
{
	return (2 * _radius*PI);
}

void Circle::draw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char BLUE[] = { 0, 0, 255 };
	const Point& c = getCenter();
	board.draw_circle(c.getX(), c.getY(), getRadius(), BLUE, 100.0f).display(disp);	
}

void Circle::clearDraw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char BLACK[] = { 0, 0, 0 };
	const Point& c = getCenter();
	board.draw_circle(c.getX(), c.getY(), getRadius(), BLACK, 100.0f).display(disp);
}
//add the the center point of the circle the new point that she input.
void Circle::move(const Point & other)
{
	_center += other;
}


