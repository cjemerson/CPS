// main.cpp
//
// Simple main to generate shapes.


#include <iostream>
#include "BasicShapes.hpp"
#include "CompoundShapes.hpp"
#include "Utilities.h"

int main(int argc, char const *argv[])
{
	auto a = Circle(80.0);
	auto b = Polygon(4, 160.0);

	auto c = Layered({a, b});
	auto d = Horizontal({c, c, c});

    makePostScriptFile(d, "anotherTestFile");

	return 0;
}
