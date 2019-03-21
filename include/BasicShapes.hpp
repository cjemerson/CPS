// BasicShapes.hpp
// Authors:
//   Charles Emerson
//
// Created: 19 Mar 2019
// Updated: 20 Mar 2019
//
// Basic Shapes Header.


#ifndef FILE_BASICSHAPES_HPP_INCLUDED
#define FILE_BASICSHAPES_HPP_INCLUDED

#include <math.h>
// For sin, cos in Polygon getBoundingBox()

#include "Shape.hpp"


// *********************************************************************
// Circle Class
// *********************************************************************

class Circle : public Shape {
public:
	Circle(double radius);

	virtual ~Circle() = default;

public:
	virtual point_t getBoundingBox() const override;

protected:
	virtual std::string generate(point_t center) const override;

protected:
	double _radius;
};


// *********************************************************************
// Circle Rectangle
// *********************************************************************

class Rectangle : public Shape {
public:
	Rectangle(double width, double height);

	virtual ~Rectangle() = default;

public:
	virtual point_t getBoundingBox() const override;

protected:
	virtual std::string generate(point_t center) const override;

protected:
	double _width, _height;
};


// *********************************************************************
// Polygon Class
// *********************************************************************

class Polygon : public Shape {
public:
	Polygon(unsigned int numSides, double sideLength);

	virtual ~Polygon() = default;

public:
	virtual point_t getBoundingBox() const override;

protected:
	virtual std::string generate(point_t center) const override;

protected:
	double _sideLength;
	unsigned int _numSides;
};


#endif // #ifndef FILE_BASICSHAPES_HPP_INCLUDED
