#pragma once

#include "Shape.h"
#include "Point.h"
#include <iostream>
#include <vector>
//#include "Cimg.h"

using namespace std;

class Polygon : public Shape
{
public:
	Polygon(const string& type, const string& name);
	virtual ~Polygon();
	// override functions if need (virtual + pure virtual)

protected:
	vector<Point> _points;
};