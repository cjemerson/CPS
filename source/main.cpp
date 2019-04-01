// main.cpp
//
// Simple main to test compilation.


#include <iostream>

#include "BasicShapes.hpp"
#include "CompoundShapes.hpp"


int main(int argc, char const *argv[])
{
	auto a = Circle(80.0);
	auto b = Polygon(4, 160.0);

	auto c = Layered({a, b});
	auto d = Ellipse(40.0, 80.0);
	auto e = Horizontal({c, d, c});

	// To print to stdout
	// std::cout << e.evaluatePostScript() << std::endl;

	// To write to output.ps
    makePostScriptFile(e, "output");

	return 0;
}
