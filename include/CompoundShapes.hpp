// CompoundShapes.hpp
//
// Compound Shapes Source.


#ifndef FILE_COMPOUNDSHAPES_HPP_INCLUDED
#define FILE_COMPOUNDSHAPES_HPP_INCLUDED


#include <functional>
// For std::reference_wrapper

#include <vector>
// For std::vector

#include <string>
// For std::string, std::to_string

#include <cmath>
// For sin and cos

#include "Shape.hpp"

#include "BasicShapes.hpp"


// *********************************************************************
// Rotated Class
// *********************************************************************

class Rotated : public Shape {
public:
	Rotated(const Shape & shape, double angleInDegrees);

	virtual ~Rotated() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	const Shape & _shape;
	double _angleInDegrees;
};


// *********************************************************************
// Scaled Class
// *********************************************************************

class Scaled : public Shape {
public:
	Scaled(const Shape & shape, double xScale, double yScale);

	virtual ~Scaled() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	const Shape & _shape;
	double _xScale, _yScale;
};


// *********************************************************************
// Layered Class
// *********************************************************************

class Layered : public Shape {
public:
	Layered(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Layered() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};


// // *********************************************************************
// // Vertical Class
// // *********************************************************************

class Vertical : public Shape {
public:
	Vertical(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Vertical() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};


// // *********************************************************************
// // Horizontal Class
// // *********************************************************************

class Horizontal : public Shape {
public:
	Horizontal(std::vector<std::reference_wrapper<const Shape>> shapeReferences);

	virtual ~Horizontal() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	std::vector<std::reference_wrapper<const Shape>> _shapeReferences;
};


class Ellipse : public Scaled{
public:
	const Circle _circle;
	Ellipse(double xRadius, double yRadius);
	virtual ~Ellipse()=default;
};

#endif // #ifndef FILE_COMPOUNDSHAPES_HPP_INCLUDED
