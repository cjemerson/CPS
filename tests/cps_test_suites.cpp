// cps_test_suites.cpp
// Original Author:
//   Glenn G. Chappell
//
// Modified Authors:
//   Charles Emerson
//
// Created: 20 Mar 2019 (from da6_test_suites.cpp)
// Updated: 20 Mar 2019
//
// For CS 372 Spring 2019
// Tests for Project 2 CPS: test suites.
// Uses the "Catch" unit-testing framework, version 2


// *********************************************************************
// Header Includes for Code to be Tested
// *********************************************************************

#include "BasicShapes.hpp"


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

#include <utility>
// For std::swap

// *********************************************************************
// Helper Classes for this Test Program
// *********************************************************************

// TestShape
// Inherited to set the center of a Shape's evaluate().
class TestShape
{
public:
	TestShape()
		: _center{0.0, 0.0}
	{ }

	virtual ~TestShape() = default;

public:
	void setCenter(point_t center)
	{
		_center = center;
	}

protected:
	point_t _center;
};

// TestCircle
// Overrides evaluate to only spit out generate() at a known center. 
class TestCircle : public Circle, public TestShape
{
public:
	TestCircle(double radius)
		: Circle(radius), TestShape()
	{ }

	std::string evaluate() const override
	{
		return generate(_center);
	}
};

// TestRectangle
// Overrides evaluate to only spit out generate() at a known center. 
class TestRectangle : public Rectangle, public TestShape
{
public:
	TestRectangle(double width, double height)
		: Rectangle(width, height), TestShape()
	{ }

	std::string evaluate() const override
	{
		return generate(_center);
	}
};

// TestPolygon
// Overrides evaluate to only spit out generate() at a known center. 
class TestPolygon : public Polygon, public TestShape
{
public:
	TestPolygon(unsigned int numSides, double sideLength)
		: Polygon(numSides, sideLength), TestShape()
	{ }

	std::string evaluate() const override
	{
		return generate(_center);
	}
};

// TestSpacer
// Overrides evaluate to only spit out generate() at a known center. 
class TestSpacer : public Spacer, public TestShape
{
public:
	TestSpacer(double width, double height)
		: Spacer(width, height), TestShape()
	{ }

	std::string evaluate() const override
	{
		return generate(_center);
	}
};


// *********************************************************************
// Helper Functions for this Test Program
// *********************************************************************

// Nothing here currently...


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

void test_circleGenerate(point_t center, double radius)
{
	using std::to_string;

	TestCircle circle(radius);
	circle.setCenter(center);

	INFO("Circle with radius " << radius << " at (" << center.x << ", " << center.y << ") generates correct PostScript");
	REQUIRE( circle.evaluate() == to_string(center.x) + " " + to_string(center.y) + " " + to_string(radius) + " circle\n" );
}

void test_rectangleGenerate(point_t center, double width, double height)
{
	using std::to_string;

	TestRectangle rectangle(width, height);
	rectangle.setCenter(center);

	INFO("Rectangle with width " << width << " and height " << height << " at (" << center.x << ", " << center.y << ") generates correct PostScript");
	REQUIRE( rectangle.evaluate() == to_string(center.x) + " " + to_string(center.y) + " " + to_string(width) + " " + to_string(height) + " rectangle\n" );
}

void test_polygonGenerate(point_t center, unsigned int numSides, double sideLength)
{
	using std::to_string;

	TestPolygon polygon(numSides, sideLength);
	polygon.setCenter(center);

	INFO("Polygon with " << numSides << " sides each of length " << sideLength << " at (" << center.x << ", " << center.y << ") generates correct PostScript");
	REQUIRE( polygon.evaluate() == to_string(center.x) + " " + to_string(center.y) + " " + to_string(sideLength) + " " + to_string(numSides) + " polygon\n" );
}

void test_spacerGenerate(point_t center, double width, double height)
{
	TestSpacer spacer(width, height);
	spacer.setCenter(center);

	INFO("Spacer with width " << width << " and height " << height << " at (" << center.x << ", " << center.y << ") generates no PostScript");
	REQUIRE( spacer.evaluate() == "" );
}


// *********************************************************************
// Test Cases for this Test Program
// *********************************************************************

TEST_CASE( "Basic Shapes - Bounding Box ", "[BasicShapes][BoundingBox]")
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
		auto list = {0.25, 1.0, 50.0, 100.0, 500.0};

		point_t center = {0.0, 0.0};
		for (auto i : list)
		{
			test_circleGenerate(center, i);
		}

		center = {500.0, 500.0};
		for (auto i : list)
		{
			test_circleGenerate(center, i);
		}

		center = {-73.07333, 499.02001};
		for (auto i : list)
		{
			test_circleGenerate(center, i);
		}
	}

	SECTION("Rectangle - PostScript Generation")
	{
		auto list = {0.25, 1.0, 50.0, 100.0, 500.0};

		point_t center = {0.0, 0.0};
		for (auto i : list)
		{
			for (auto j : list)
			{
				test_rectangleGenerate(center, i, j);
			}
		}

		center = {500.0, 500.0};
		for (auto i : list)
		{
			for (auto j : list)
			{
				test_rectangleGenerate(center, i, j);
			}
		}

		center = {-73.07333, 499.02001};
		for (auto i : list)
		{
			for (auto j : list)
			{
				test_rectangleGenerate(center, i, j);
			}
		}
	}

	SECTION("Polygon - PostScript Generation")
	{
		auto sideLength_list = {0.25, 1.0, 50.0, 100.0, 500.0};
		auto numSides_list = {2, 3, 4, 5, 6, 8, 11, 19};

		point_t center = {0.0, 0.0};
		for (auto sideLength : sideLength_list)
		{
			for (auto numSides : numSides_list)
			{
				test_polygonGenerate(center, numSides, sideLength);
			}
		}

		center = {500.0, 500.0};
		for (auto sideLength : sideLength_list)
		{
			for (auto numSides : numSides_list)
			{
				test_polygonGenerate(center, numSides, sideLength);
			}
		}

		center = {-73.07333, 499.02001};
		for (auto sideLength : sideLength_list)
		{
			for (auto numSides : numSides_list)
			{
				test_polygonGenerate(center, numSides, sideLength);
			}
		}
	}

	SECTION("Spacer - PostScript Generation")
	{
		auto list = {0.25, 1.0, 50.0, 100.0, 500.0};

		point_t center = {0.0, 0.0};
		for (auto i : list)
		{
			for (auto j : list)
			{
				test_spacerGenerate(center, i, j);
			}
		}

		center = {500.0, 500.0};
		for (auto i : list)
		{
			for (auto j : list)
			{
				test_spacerGenerate(center, i, j);
			}
		}

		center = {-73.07333, 499.02001};
		for (auto i : list)
		{
			for (auto j : list)
			{
				test_spacerGenerate(center, i, j);
			}
		}
	}
}
