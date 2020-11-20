#pragma once
#include "Polygon.h"

class Triangle : public Polygon
{
public:
	Triangle(const Point& a, const Point& b, const Point& c, const string& type, const string& name);
	virtual ~Triangle();
	double getArea() const;
	double getPerimeter() const;
	void move(const Point& other);
	virtual void draw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board);
	virtual void clearDraw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board);
	// override functions if need (virtual + pure virtual)
};