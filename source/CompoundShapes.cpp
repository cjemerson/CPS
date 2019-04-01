// CompoundShapes.cpp
//
// Compound Shapes Source.


#include "CompoundShapes.hpp"


// *********************************************************************
// Rotated Class
// *********************************************************************

Rotated::Rotated(const Shape & shape, double angleInDegrees)
	: _shape(shape), _angleInDegrees(angleInDegrees)
{ }

point_t Rotated::getBoundingBox() const
{
	const double PI = 3.14159265358979323846;

	// To access other Shapes' protected getBoundingBox need
	// to pass a ShapeKey to the public getBoundingBox
	double x = _shape.getBoundingBox({}).x;
	double y = _shape.getBoundingBox({}).y;
	double o = PI * _angleInDegrees / 180.0;

	double height = abs(x * sin(o)) + abs(y * cos(o));
	double width = abs(x * cos(o)) + abs(y * sin(o));

	return {width, height};
}

std::string Rotated::generate(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_angleInDegrees) + " rotateAbout\n"
			+ _shape.generate(center, {}) + "grestore\n";
}


// *********************************************************************
// Scaled Class
// *********************************************************************

Scaled::Scaled(const Shape & shape, double xScale, double yScale)
	: _shape(shape), _xScale(xScale), _yScale(yScale)
{ }


point_t Scaled::getBoundingBox() const
{
	// To access other Shapes' protected getBoundingBox need
	// to pass a ShapeKey to the public getBoundingBox
	auto result = _shape.getBoundingBox({});

	result.x *= _xScale;
	result.y *= _yScale;

	return result;
}

std::string Scaled::generate(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_xScale) + " " + to_string(_yScale)
			+ " scaleAbout\n" + _shape.generate(center, {})
			+ "grestore\n";
}



// *********************************************************************
// Layered Class
// *********************************************************************

Layered::Layered(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: _shapeReferences(std::move(shapeReferences))
{ }

point_t Layered::getBoundingBox() const
{
	point_t result = {0.0, 0.0};

	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		auto shapeBoundingBox = shape.getBoundingBox({});

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

	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		output += shape.generate(center, {});
	}

	return output;
}


// *********************************************************************
// Vertical Class
// *********************************************************************

Vertical::Vertical(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: _shapeReferences(std::move(shapeReferences))
{ }


point_t Vertical::getBoundingBox() const
{
	point_t result = {0.0, 0.0};

	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		auto shapeBoundingBox = shape.getBoundingBox({});

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

	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		auto shapeHeight = shape.getBoundingBox({}).y;

		y += shapeHeight / 2.0;
		output += shape.generate({x, y}, {});
		y += shapeHeight / 2.0;
	}

	return output;
}


// *********************************************************************
// Horizontal Class
// *********************************************************************

Horizontal::Horizontal(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: _shapeReferences(std::move(shapeReferences))
{ }

point_t Horizontal::getBoundingBox() const
{
	point_t result = {0.0, 0.0};

	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		auto shapeBoundingBox = shape.getBoundingBox({});

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

	for (auto shapeReference : _shapeReferences)
	{
		// To use list of Shapes needed reference_wrapper<const Shape>
		// which is dereferenced with get()
		const Shape & shape = shapeReference.get();

		// To access other Shapes' protected getBoundingBox need
		// to pass a ShapeKey to the public getBoundingBox
		auto shapeWidth = shape.getBoundingBox({}).x;

		x += shapeWidth / 2.0;
		output += shape.generate({x, y}, {});
		x += shapeWidth / 2.0;
	}

	return output;
}

Ellipse::Ellipse(double xRadius, double yRadius): _circle(std::min(xRadius, yRadius)), 
Scaled(_circle, std::min(xRadius/yRadius, 1.0), std::min(yRadius/xRadius, 1.0))
{}