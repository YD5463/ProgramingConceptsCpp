#include "Arrow.h"


//constractor
Arrow::Arrow(const Point & a, const Point & b, const string & type, const string & name):Shape(name,type),_p1(a),_p2(b)
{
}
//anther defult constractor
Arrow::~Arrow()
{
}

void Arrow::draw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char RED[] = { 255, 0, 0 };

	board.draw_arrow(_p1.getX(), _p1.getY(),
		_p2.getX(), _p2.getY(), RED, 100.0f).display(disp);
}
void Arrow::clearDraw(cimg_library::CImgDisplay& disp, cimg_library::CImg<unsigned char>& board)
{
	unsigned char BLACK[] = { 0, 0, 0 };

	board.draw_arrow(_p1.getX(), _p1.getY(),
		_p2.getX(), _p2.getY(), BLACK, 100.0f).display(disp);
}
//calc and return the peramiter of the arrow(the distance)
double Arrow::getPerimeter() const
{
	return _p1.distance(_p2);
}
//add to the points of the arrow the input point
void Arrow::move(const Point & other)
{
	_p1 += other;
	_p2 += other;
}
//return 0 becuse the area of arrow is allways 0.
double Arrow::getArea() const
{
	return 0;
}


