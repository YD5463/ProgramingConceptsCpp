#pragma once
#include "Point.h"
#include <math.h>
//constractor
Point::Point(double x, double y):_x(x),_y(y)
{
}

Point::Point()
{

}
//copy constractor
Point::Point(const Point & other)
{
	_x = other._x;
	_y = other._y;
}

Point::~Point()
{
}
/*
create a new point and insert to him the adding between the points
and reurn the new point.
*/
Point Point::operator+(const Point & other) const
{
	Point temp(this->_x,this->_y);
	temp._x = this->_x + other._x;
	temp._y =  this->_y + other._y;
	return temp;
}
/*
add between two points and reurn pointer of the point
*/
Point & Point::operator+=(const Point & other)
{
	this->_x += other._x;
	this->_y += other._y;
	return *this;
}
//return the x of the point
double Point::getX() const
{
	return _x;
}
//return the y of the point
double Point::getY() const
{
	return _y;
}
/*
calc the distance between two points
*/
double Point::distance(const Point & other) const
{
	return sqrt(pow((other._x - _x), 2) + pow((other._y - _y), 2));
}
