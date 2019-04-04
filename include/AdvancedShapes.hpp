// AdvancedShapes.hpp
//
// Advanced Shapes Header.


#ifndef FILE_ADVANCEDSHAPES_HPP_INCLUDED
#define FILE_ADVANCEDSHAPES_HPP_INCLUDED


#include <vector>
// For std::vector

#include <functional>
// For std::reference_wrapper

#include <cmath>
// For std::abs

#include "BasicShapes.hpp"
// For Circle, Spacer

#include "CompoundShapes.hpp"
// For Scaled, Layered, Vertical, Rotated


// *********************************************************************
// Ellipse Class
// *********************************************************************

class Ellipse : public Scaled {
public:
	Ellipse(double xRadius, double yRadius);

	virtual ~Ellipse() = default;

protected:
	const Circle _circle;
};


// *********************************************************************
// Donut class
// *********************************************************************

class Donut : public Layered {
public:
    Donut(unsigned int numCircles, double offsetR, double subcircleR);

    virtual ~Donut() = default;

protected:
    point_t getBoundingBox() const override;

protected:
    double _maxR;
    const Circle _circle;
    const Spacer _spacer;
    const Vertical _vertical;
    std::vector<Rotated> _listOfRotated;
};


#endif // #ifndef FILE_ADVANCEDSHAPES_HPP_INCLUDED
