// Shape.cpp
//
// Basic Shapes Source.


#include "Shape.hpp"
#include "Utilities.h"

// *********************************************************************
// Shape Class Source
// *********************************************************************

std::string Shape::evaluatePostScript() const
{
    const point_t center = {8.5*72.0/2.0, 11.0*72.0/2.0};

    return getPostScriptHeader() + generatePostScript(center) + "\nshowpage\n";
}
