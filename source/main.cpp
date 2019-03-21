// main.cpp
// Authors:
//   Charles Emerson
//
// Created: 19 Mar 2019
// Updated: 20 Mar 2019
//
// Simple main to test compilation.


#include <iostream>

#include "BasicShapes.hpp"


int main(int argc, char const *argv[])
{
	Circle a(150.0);

	std::cout << a.evaluate() << std::endl;

	return 0;
}
