#pragma once

#include "Shape.h"
#include "Point.h"
#include <vector>
#define PI 3.14

class Circle : public Shape
{
public:
	Circle(const Point& center, double radius, const string& type, const string& name);
	~Circle();

	const Point& getCenter() const;
	double getRadius() const;
	double getArea() const;
	double getPerimeter() const;
	virtual void draw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board);
	virtual void clearDraw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board);
	void move(const Point& other);
	// override functions if need (virtual + pure virtual)
protected:
	Point _center;
	double _radius;
};