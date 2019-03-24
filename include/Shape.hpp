// Shape.hpp
// Authors:
//   Charles Emerson
//
// Created: 19 Mar 2019
// Updated: 20 Mar 2019
//
// Basic Shapes Source.


#ifndef FILE_SHAPE_HPP_INCLUDED
#define FILE_SHAPE_HPP_INCLUDED

#include <string>
#include <memory>


// *********************************************************************
// Point Type
// *********************************************************************

struct point_t {
	double x;
	double y;
};


// *********************************************************************
// (Abstract) Shape Class
// *********************************************************************

class Shape {	
private:
	struct ShapeKey {};

public:
	virtual ~Shape() = default;

public:
	// To generate the PostScript to draw a Shape:
	virtual std::string evaluate() const;

public:
	virtual point_t getBoundingBox(ShapeKey key) const
	{
		(void) key;

		return getBoundingBox();
	}

	virtual std::string generate(point_t center, ShapeKey key) const
	{
		(void) key;

		return generate(center);
	}

protected:
	// A new type of shape needs to have these defined
	virtual point_t getBoundingBox() const = 0;
	virtual std::string generate(point_t center) const = 0;

};


#endif // #ifndef FILE_SHAPE_HPP_INCLUDED
