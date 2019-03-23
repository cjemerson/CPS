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
	const double PI = 3.14159265358979323846;

	double x = _shape->getBoundingBox({}).x;
	double y = _shape->getBoundingBox({}).y;
	double o = PI * _angleInDegrees / 180.0;

	double height = abs(x * sin(o)) + abs(y * cos(o));
	double width = abs(x * cos(o)) + abs(y * sin(o));

	return {width, height};
}

std::string Rotated::generate(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_angleInDegrees) + " rotatedAbout\n"
			+ _shape->generate(center, {}) + "grestore\n";
}


// *********************************************************************
// Scaled Class
// *********************************************************************

Scaled::Scaled(Shape::ptr_t shape, double xScale, double yScale)
	: _shape(std::move(shape)), _xScale(xScale), _yScale(yScale)
{ }


point_t Scaled::getBoundingBox() const
{
	auto result = _shape->getBoundingBox({});

	result.x *= _xScale;
	result.y *= _yScale;

	return result;
}

std::string Scaled::generate(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_xScale) + " " + to_string(_yScale)
			+ " scaledAbout\n" + _shape->generate(center, {})
			+ "grestore\n";
}



// *********************************************************************
// Layered Class
// *********************************************************************

Layered::Layered(std::vector<Shape::ptr_t> shapes)
	: _shapes(std::move(shapes))
{ }

point_t Layered::getBoundingBox() const
{
	point_t result = {0.0, 0.0};

	for (ptrToAShape : _shapes)
	{
		auto shapeBoundingBox = ptrToAShape->getBoundingBox({});

		if (shapeBoundingBox.x > result.x)
			result.x = shapeBoundingBox.x;

		if (shapeBoundingBox.y > result.y)
			result.y = shapeBoundingBox.y;
	}

	return result;
}

std::string Layered::generate(point_t center) const
{
	std::string output = "";

	for (ptrToAShape : _shapes)
	{
		output += ptrToAShape->generate(center, {});
	}

	return output;
}


// *********************************************************************
// Vertical Class
// *********************************************************************

Vertical::Vertical(std::vector<Shape::ptr_t> shapes)
	: _shapes(std::move(shapes))
{ }


point_t Vertical::getBoundingBox() const
{
	point_t result;

	for (ptrToAShape : _shapes)
	{
		auto shapeBoundingBox = ptrToAShape->getBoundingBox({}); 

		// Output the largest width
		if (shapeBoundingBox.x > result.x)
			result.x = shapeBoundingBox.x;

		// Sum the heights
		result.y += shapeBoundingBox.y;
	}

	return result;
}

std::string Vertical::generate(point_t center) const
{
	auto height = getBoundingBox().y;

	std::string output = "";

	auto x = center.x;
	auto y = center.y - (height / 2.0);

	for (ptrToAShape : _shapes)
	{
		auto shapeHeight = ptrToAShape->getBoundingBox({}).y;

		y += shapeHeight / 2.0;
		output += ptrToAShape->generate({x, y}, {});
		y += shapeHeight / 2.0;
	}

	return output;
}


// *********************************************************************
// Horizontal Class
// *********************************************************************

Horizontal::Horizontal(std::vector<Shape::ptr_t> shapes)
	: _shapes(std::move(shapes))
{ }

point_t Horizontal::getBoundingBox() const
{
	point_t result;

	for (ptrToAShape : _shapes)
	{
		auto shapeBoundingBox = ptrToAShape->getBoundingBox({}); 

		// Sum the widths
		result.x += shapeBoundingBox.x;

		// Output the largest height
		if (shapeBoundingBox.y > result.y)
			result.y = shapeBoundingBox.y;
	}

	return result;
}

std::string Horizontal::generate(point_t center) const
{
	auto width = getBoundingBox().x;

	std::string output = "";

	auto x = center.x - (width / 2.0);
	auto y = center.y;

	for (ptrToAShape : _shapes)
	{
		auto shapeWidth = ptrToAShape->getBoundingBox({}).x;

		x += shapeWidth / 2.0;
		output += ptrToAShape->generate({x, y}, {});
		x += shapeWidth / 2.0;
	}

	return output;
}
