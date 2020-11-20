#pragma once
#include "Polygon.h"

class Arrow : public Shape
{
public:
	Arrow(const Point& a, const Point& b, const string& type, const string& name);
	~Arrow();

	virtual void draw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board);
	virtual void clearDraw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board);
	double getArea() const;
	double getPerimeter() const;
	void move(const Point& other);
	// override functions if need (virtual + pure virtual)

private:
	Point _p1;
	Point _p2;
};