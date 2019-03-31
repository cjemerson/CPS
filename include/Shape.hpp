// Shape.hpp
//
// Basic Shapes Source.


#ifndef FILE_SHAPE_HPP_INCLUDED
#define FILE_SHAPE_HPP_INCLUDED

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

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
	virtual std::string evaluatePostScript() const;

public:
	virtual point_t getBoundingBox(ShapeKey key) const
	{
		(void) key;

		return getBoundingBox();
	}

	virtual std::string generatePostScript(point_t center, ShapeKey key) const
	{
		(void) key;

		return generatePostScript(center);
	}

protected:
	// A new type of shape needs to have these defined
	virtual point_t getBoundingBox() const = 0;
	virtual std::string generatePostScript(point_t center) const = 0;

};

// *********************************************************************
// Utility Functions
// *********************************************************************

std::string getPostScriptHeader();

void makePostScriptFile(const Shape & shape, std::string filename);

#endif // #ifndef FILE_SHAPE_HPP_INCLUDED
