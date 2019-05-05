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

std::string Rotated::generatePostScript(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_angleInDegrees) + " rotateAbout\n"
			+ _shape.generatePostScript(center, {}) + "grestore\n";
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

std::string Scaled::generatePostScript(point_t center) const
{
	using std::to_string;

	return "gsave\n" + to_string(center.x) + " " + to_string(center.y)
			+ " " + to_string(_xScale) + " " + to_string(_yScale)
			+ " scaleAbout\n" + _shape.generatePostScript(center, {})
			+ "grestore\n";
}


// *********************************************************************
// Overlay Class
// *********************************************************************

Overlay::Overlay(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: _shapeReferences(std::move(shapeReferences))
{ }


// *********************************************************************
// Layered Class
// *********************************************************************

Layered::Layered(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: Overlay(std::move(shapeReferences))
{ }

point_t Layered::getBoundingBox() const
{
	return std::accumulate(
		_shapeReferences.begin(),
		_shapeReferences.end(),
		point_t{0.0, 0.0},
		[](point_t current, const auto & shape) {
			auto bb = shape.get().getBoundingBox({});
			return point_t{
				std::max(current.x, bb.x),
				std::max(current.y, bb.y),
			};
		});
}

std::string Layered::generatePostScript(point_t center) const
{
	return std::accumulate(
		_shapeReferences.begin(),
		_shapeReferences.end(),
		std::string(""),
		[&](auto current, const auto & shape) {
			return std::move(current)
				+ std::move(shape.get().generatePostScript(center, {}));
		});
}


// *********************************************************************
// Vertical Class
// *********************************************************************

Vertical::Vertical(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: Overlay(std::move(shapeReferences))
{ }


point_t Vertical::getBoundingBox() const
{
	return std::accumulate(
		_shapeReferences.begin(),
		_shapeReferences.end(),
		point_t{0.0, 0.0},
		[](point_t current, const auto & shape) {
			auto bb = shape.get().getBoundingBox({});
			return point_t{
				std::max(current.x, bb.x),
				current.y + std::abs(bb.y),
			};
		});
}

std::string Vertical::generatePostScript(point_t center) const
{
	auto height = getBoundingBox().y;

	auto x = center.x;
	auto y = center.y - (height / 2.0);

	return std::accumulate(
		_shapeReferences.begin(),
		_shapeReferences.end(),
		std::string(""),
		[&](auto current, const auto & shape) {
			auto halfHeight = shape.get().getBoundingBox({}).y / 2.0;
			y += halfHeight;
			auto oldY = y;
			y += halfHeight;
			return std::move(current) + std::move(shape.get().generatePostScript({x, oldY}, {}));
		});
}


// *********************************************************************
// Horizontal Class
// *********************************************************************

Horizontal::Horizontal(std::vector<std::reference_wrapper<const Shape>> shapeReferences)
	: Overlay(std::move(shapeReferences))
{ }

point_t Horizontal::getBoundingBox() const
{
	return std::accumulate(
		_shapeReferences.begin(),
		_shapeReferences.end(),
		point_t{0.0, 0.0},
		[](point_t current, const auto & shape) {
			auto bb = shape.get().getBoundingBox({});
			return point_t{
				current.x + bb.x,
				std::max(current.y, bb.y),
			};
		});
}

std::string Horizontal::generatePostScript(point_t center) const
{
	auto width = getBoundingBox().x;

	auto x = center.x - (width / 2.0);
	auto y = center.y;

	return std::accumulate(
		_shapeReferences.begin(),
		_shapeReferences.end(),
		std::string(""),
		[&](auto current, const auto & shape) {
			auto halfWidth = shape.get().getBoundingBox({}).x / 2.0;
			x += halfWidth;
			auto oldX = x;
			x += halfWidth;
			return std::move(current) + std::move(shape.get().generatePostScript({oldX, y}, {}));
		});
}
