#include "Polygon.h"
//constractor of Polygon 
Polygon::Polygon(const string & type, const string & name):Shape(name,type),_points(0)
{
}

Polygon::~Polygon()
{
}
