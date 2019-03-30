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
	auto d = Horizontal({c, c, c});

	std::cout << d.evaluatePostScript() << std::endl;

	return 0;
}
