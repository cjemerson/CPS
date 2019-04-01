// BasicShapes.cpp
//
// Basic Shapes Source.


#include "BasicShapes.hpp"


// *********************************************************************
// Circle Class
// *********************************************************************

Circle::Circle(double radius)
	: _radius(radius)
{ }

point_t Circle::getBoundingBox() const
{
	return {2 * _radius, 2 * _radius};
}

std::string Circle::generatePostScript(point_t center) const
{
	using std::to_string;

	return to_string(center.x) + " " + to_string(center.y) + " "
			+ to_string(_radius) + " circle\n";
}


// *********************************************************************
// Rectangle Class
// *********************************************************************

Rectangle::Rectangle(double width, double height)
	: _width(width), _height(height)
{ }

point_t Rectangle::getBoundingBox() const
{
	return {_width, _height};
}

std::string Rectangle::generatePostScript(point_t center) const {
	using std::to_string;

	return to_string(center.x) + " " + to_string(center.y) + " "
			+ to_string(_width) + " " + to_string(_height)
			+ " rectangle\n";
}


// *********************************************************************
// (Regular) Polygon Class
// *********************************************************************

Polygon::Polygon(unsigned int numSides, double sideLength)
	: _sideLength(sideLength), _numSides(numSides)
{ }

point_t Polygon::getBoundingBox() const
{
	const auto n = _numSides;
	const double e = _sideLength;
	const double pi = 3.14159265358979323846;

	double width, height;

	// Case 1: n is odd.
	// height = e(1+cos(π/n))/(2sin(π/n))
	// width = (e sin(π(n-1)/2n))/(sin(π/n))
	if (n % 2 == 1)
	{
		height = e*(1+cos(pi/n))/(2*sin(pi/n));
		width = (e*sin(pi*(n-1)/2*n))/(sin(pi/n));
	}
	// Case 2: n is divisible by 4.
	// height = e(cos(π/n))/(sin(π/n))
	// width = (e cos(π/n))/(sin(π/n))
	else if (n % 4 == 0){
		height = e*(cos(pi/n))/(sin(pi/n));
		width = (e*cos(pi/n))/(sin(pi/n));
	}
	// Case 3: n is divisible by 2, but not by 4.
	// height = e(cos(π/n))/(sin(π/n))
	// width = e/(sin(π/n))
	else
	{
		height = e*(cos(pi/n))/(sin(pi/n));
		width = e/(sin(pi/n));
	}

	return {width, height};
}

std::string Polygon::generatePostScript(point_t center) const
{
	using std::to_string;

	return to_string(center.x) + " " + to_string(center.y) + " "
			+ to_string(_sideLength) + " " + to_string(_numSides)
			+ " polygon\n";
}


// *********************************************************************
// Spacer Class
// *********************************************************************

Spacer::Spacer(double width, double height)
	: _width(width), _height(height)
{ }

point_t Spacer::getBoundingBox() const
{
	return {_width, _height};
}

std::string Spacer::generatePostScript(point_t center) const
{
	return "";
}



Square::Square(double sideLength): Rectangle(sideLength, sideLength)
{}

Triangle::Triangle(double length): Polygon(3, length)
{}
