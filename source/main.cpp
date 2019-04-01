// main.cpp
//
// Simple main to generate shapes.


#include <iostream>
#include "BasicShapes.hpp"
#include "CompoundShapes.hpp"
#include "Utilities.h"

int main(int argc, char const *argv[])
{
	auto a = Square(40.0);
    auto b = Polygon(5, 50.0);
    auto c = Polygon(8, 80.0);
    auto triangle = Triangle(50.0);

    auto d = Horizontal({b,triangle});

    makePostScriptFile(d, "HorizontalPolygonS5L50TriangleS50");

	return 0;
}
