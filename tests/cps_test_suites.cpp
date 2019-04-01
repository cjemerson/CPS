// cps_test_suites.cpp
//
// Created from da6_test_main.cpp by Glenn G. Chappell.
//
// For CS 372 Spring 2019
// Tests for Project 2 CPS: test suites.
// Uses the "Catch" unit-testing framework, version 2


// *********************************************************************
// Header Includes for Code to be Tested
// *********************************************************************

#include "BasicShapes.hpp"
#include "CompoundShapes.hpp"
#include "Utilities.h"

// *********************************************************************
// catch.hpp
// *********************************************************************

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework


// *********************************************************************
// Additional Includes for this Test Program
// *********************************************************************

#include <string>
// For std::string, std::to_string

// *********************************************************************
// Test Functions for this Test Program
// *********************************************************************

void test_circleBoundingBox(double radius)
{
	Circle circle(radius);

	INFO("A Circle with radius " << radius << " has a bounding box with (" << 2 * radius << ", " << 2 * radius << ")");
	REQUIRE( circle.getBoundingBox().x == 2 * radius );
	REQUIRE( circle.getBoundingBox().y == 2 * radius );
}

void test_rectangleBoundingBox(double width, double height)
{
	Rectangle rectangle(width, height);
	INFO("A Rectangle with width " << width << " and height " << height << " has a bounding box with width " << width << " and height " << height);
	REQUIRE( rectangle.getBoundingBox().x == width);
	REQUIRE( rectangle.getBoundingBox().y == height);
}

void test_polygonBoundingBox(unsigned int numSides, double sideLength)
{
	Polygon polygon(numSides, sideLength);

	double width, height;

	const auto n = numSides;
	const double e = sideLength;
	const double pi = 3.14159265358979323846;

	// Case 1: n is odd.
	// height = e(1+cos(π/n))/(2sin(π/n))
	// width = (e sin(π(n-1)/2n))/(sin(π/n))
	if (n % 2 == 1)
	{
		height = e*(1+cos(pi/n))/(2*sin(pi/n));
		width = (e*sin(pi*(n-1)/2*n))/(sin(pi/n));
	}
	// Case 2: n is divisible by 4.
	// height = e(cos(π/n))/(sin(π/n))
	// width = (e cos(π/n))/(sin(π/n))
	else if (n % 4 == 0){
		height = e*(cos(pi/n))/(sin(pi/n));
		width = (e*cos(pi/n))/(sin(pi/n));
	}
	// Case 3: n is divisible by 2, but not by 4.
	// height = e(cos(π/n))/(sin(π/n))
	// width = e/(sin(π/n))
	else
	{
		height = e*(cos(pi/n))/(sin(pi/n));
		width = e/(sin(pi/n));
	}

	INFO("Polygon with " << numSides << " sides each of length " << sideLength << " has a bounding box with width " << width << " and height " << height);
	REQUIRE(polygon.getBoundingBox().x == Approx(width));
	REQUIRE(polygon.getBoundingBox().y == Approx(height));
}

void test_spacerBoundingBox(double width, double height)
{
	Spacer spacer(width, height);
	INFO("A Spacer with width " << width << " and height " << height << " has a bounding box with width " << width << " and height " << height);
	REQUIRE( spacer.getBoundingBox().x == width);
	REQUIRE( spacer.getBoundingBox().y == height);
}



// *********************************************************************
// Test Cases for this Test Program
// *********************************************************************

TEST_CASE( "Basic Shapes - Bounding Box ", "[BasicShapes][BoundingBox]" )
{
	SECTION("Circle - Bounding Box")
	{
		auto list = {0.25, 1.0, 50.0, 100.0, 500.0};

		for (auto i : list)
		{
			test_circleBoundingBox(i);
		}
	}

	SECTION("Rectangle - Bounding Box")
	{
		auto list = {0.25, 1.0, 50.0, 100.0, 500.0};

		for (auto i : list)
		{
			for (auto j : list)
			{
				test_rectangleBoundingBox(i, j);
			}
		}
	}

	SECTION("Polygon - Bounding Box")
	{
		auto sideLength_list = {0.25, 1.0, 50.0, 100.0, 500.0};
		auto numSides_list = {3, 4, 5, 6, 8, 11, 19};

		for (auto sideLength : sideLength_list)
		{
			for (auto numSides : numSides_list)
			{
				test_polygonBoundingBox(numSides, sideLength);
			}
		}
	}

	SECTION("Spacer - Bounding Box")
	{
		auto list = {0.25, 1.0, 50.0, 100.0, 500.0};

		for (auto i : list)
		{
			for (auto j : list)
			{
				test_spacerBoundingBox(i, j);
			}
		}
	}
}

TEST_CASE( "Basic Shapes - PostScript Generation", "[BasicShapes][PostScript]" )
{
	SECTION("Circle - PostScript Generation")
	{
	}

	SECTION("Rectangle - PostScript Generation")
	{
	}

	SECTION("Polygon - PostScript Generation")
	{
	}

	SECTION("Spacer - PostScript Generation")
	{
	}
}
