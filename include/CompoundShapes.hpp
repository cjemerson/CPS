// CompoundShapes.hpp
// Authors:
//   Charles Emerson
//
// Created: 22 Mar 2019
// Updated: 22 Mar 2019
//
// Compound Shapes Source.


#ifndef FILE_COMPOUNDSHAPES_HPP_INCLUDED
#define FILE_COMPOUNDSHAPES_HPP_INCLUDED


#include <vector>
// For std::vector

#include <string>
// For std::string, std::to_string

#include <cmath>
// For sin and cos

#include "Shape.hpp"


// *********************************************************************
// Rotated Class
// *********************************************************************

class Rotated : public Shape {
public:
	Rotated(Shape::ptr_t shape, double angleInDegrees);

	virtual ~Rotated() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	Shape::ptr_t _shape;
	double _angleInDegrees;
};


// *********************************************************************
// Scaled Class
// *********************************************************************

class Scaled : public Shape {
public:
	Scaled(Shape::ptr_t shape, double xScale, double yScale);

	virtual ~Scaled() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	Shape::ptr_t _shape;
	double _xScale, _yScale;
};


// *********************************************************************
// Layered Class
// *********************************************************************

class Layered : public Shape {
public:
	Layered(std::vector<Shape::ptr_t> shapes);

	virtual ~Layered() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	std::vector<Shape::ptr_t> _shapes;
};


// *********************************************************************
// Vertical Class
// *********************************************************************

class Vertical : public Shape {
public:
	Vertical(std::vector<Shape::ptr_t> shapes);

	virtual ~Vertical() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	std::vector<Shape::ptr_t> _shapes;
};


// *********************************************************************
// Horizontal Class
// *********************************************************************

class Horizontal : public Shape {
public:
	Horizontal(std::vector<Shape::ptr_t> shapes);

	virtual ~Horizontal() = default;

protected:
	virtual point_t getBoundingBox() const override;
	virtual std::string generate(point_t center) const override;

protected:
	std::vector<Shape::ptr_t> _shapes;
};


#endif // #ifndef FILE_COMPOUNDSHAPES_HPP_INCLUDED
