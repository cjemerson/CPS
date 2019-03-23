// CompoundShapes.cpp
// Authors:
//   Charles Emerson
//
// Created: 22 Mar 2019
// Updated: 22 Mar 2019
//
// Compound Shapes Source.


#include "CompoundShapes.hpp"


// *********************************************************************
// Rotated Class
// *********************************************************************

Rotated::Rotated(Shape::ptr_t shape, double angleInDegrees)
	: _shape(std::move(shape)), _angleInDegrees(angleInDegrees)
{ }

point_t Rotated::getBoundingBox() const
{
	// @TODO
	return {0.0, 0.0};
}
std::string Rotated::generate(point_t center) const
{
	// @TODO
	return "";
}


// *********************************************************************
// Scaled Class
// *********************************************************************

Scaled::Scaled(Shape::ptr_t shape, double xScale, double yScale)
	: _shape(std::move(shape)), _xScale(xScale), _yScale(yScale)
{ }


point_t Scaled::getBoundingBox() const
{
	// @TODO
	return {0.0, 0.0};
}

std::string Scaled::generate(point_t center) const
{
	// @TODO
	return "";
}



// *********************************************************************
// Layered Class
// *********************************************************************

Layered::Layered(std::vector<Shape::ptr_t> shapes)
	: _shapes(std::move(shapes))
{ }

point_t Layered::getBoundingBox() const
{
	// @TODO
	return {0.0, 0.0};
}

std::string Layered::generate(point_t center) const
{
	// @TODO
	return "";
}


// *********************************************************************
// Vertical Class
// *********************************************************************

Vertical::Vertical(std::vector<Shape::ptr_t> shapes)
	: _shapes(std::move(shapes))
{ }


point_t Vertical::getBoundingBox() const
{
	// @TODO
	return {0.0, 0.0};
}
std::string Vertical::generate(point_t center) const
{
	return "";
}


// *********************************************************************
// Horizontal Class
// *********************************************************************

Horizontal::Horizontal(std::vector<Shape::ptr_t> shapes)
	: _shapes(std::move(shapes))
{ }

point_t Horizontal::getBoundingBox() const
{
	// @TODO
	return {0.0, 0.0};
}

std::string Horizontal::generate(point_t center) const
{
	// @TODO
	return "";
}
