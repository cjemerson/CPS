// BasicShapes.cpp
// Authors:
//   Charles Emerson
//
// Created: 19 Mar 2019
// Updated: 20 Mar 2019
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

std::string Circle::generate(point_t center) const
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

std::string Rectangle::generate(point_t center) const {
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
	const double PI = 3.141592653589793;

	auto n = _numSides;
	auto e = _sideLength;

	auto piDivN = PI/n;
	auto cos_piDivN = cos(piDivN);
	auto sin_piDivN = sin(piDivN);

	if ( n % 1 )
	{
		return {e * sin( PI*(n-1) / (2*n) ) / sin_piDivN,
				e * (1 + cos_piDivN) / (2 * sin_piDivN)};
	}
	else if (n % 4 == 0)
	{
		auto temp = e * cos_piDivN / sin_piDivN;
		return {temp, temp};
	}
	else // if (n % 2 == 0 && ! (n % 4 == 0))
	{
		return {e * cos_piDivN / sin_piDivN,
				e / sin_piDivN};
	}
}

std::string Polygon::generate(point_t center) const
{
	using std::to_string;

	return to_string(center.x) + " " + to_string(center.y) + " "
			+ to_string(_sideLength) + " " + to_string(_numSides)
			+ " polygon\n";
}
