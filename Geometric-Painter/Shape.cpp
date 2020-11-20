#include "Shape.h"
#include "string"
//constractor of shape
Shape::Shape(const string & name, const string & type)
{
	_name = name;
	_type = type;
}
//print the details about the shape
void Shape::printDetails() const
{
	std::cout << _type << "  " << _name <<"		"<<this->getArea()<<"    "<<this->getPerimeter()<< std::endl;
}
//return the type of the shape
string Shape::getType() const
{
	return _type;
}
//return the name
string Shape::getName() const
{
	return _name;
}
