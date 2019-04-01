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

void test_shapePostScriptGeneration(const std::string & filename, const Shape & shape)
{
    std::string testFilePath = "../tests/testfiles/" + filename;
    std::ifstream file(testFilePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string shapePostScript = shape.evaluatePostScript();
    REQUIRE(buffer.str() == shapePostScript);
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

TEST_CASE( "Basic Shapes - PostScript File Generation", "[BasicShapes][PostScript]" )
{
	SECTION("Circle - PostScript File Generation")
	{
	    INFO("Checking Circle - Radius 80, 180");
        auto testCircle1 = Circle(80);
        auto testCircle2 = Circle(180);
        test_shapePostScriptGeneration("CircleR80.ps", testCircle1);
        test_shapePostScriptGeneration("CircleR180.ps", testCircle2);
	}

	SECTION("Rectangle - PostScript File Generation")
	{
	    INFO("Checking Rectangle - 80x60, 120x200");
	    auto testRectangle1 = Rectangle(80.0, 60.0);
	    auto testRectangle2 = Rectangle(120.0, 200.0);
	    test_shapePostScriptGeneration("RectangleW80H60.ps", testRectangle1);
        test_shapePostScriptGeneration("RectangleW120H200.ps", testRectangle2);
	}

	SECTION("Polygon - PostScript File Generation")
	{
		INFO("Checking Polygon - Pentagon L=50, Hexagon L=66.6, Heptagon L=77.7")
		auto testPolygon1 = Polygon(5,50.0);
		auto testPolygon2 = Polygon(6,66.6);
		auto testPolygon3 = Polygon(7,77.7);
		test_shapePostScriptGeneration("PolygonS5L50.ps", testPolygon1);
		test_shapePostScriptGeneration("PolygonS6L66.6.ps", testPolygon2);
		test_shapePostScriptGeneration("PolygonS7L77.7.ps", testPolygon3);
	}

	SECTION("Square - PostScript File Generation")
	{
		INFO("Checking Square - L=45.5, L=120");
		auto testSquare1 = Square(45.5);
		auto testSquare2 = Square(120);
		test_shapePostScriptGeneration("SquareL45.5.ps", testSquare1);
		test_shapePostScriptGeneration("SquareL120.ps", testSquare2);
	}

	SECTION("Triangle - PostScript File Generation")
	{
		INFO("Checking Triangle - L=60");
		auto testTriangle = Triangle(60.0);
		test_shapePostScriptGeneration("TriangleS60.ps", testTriangle);
	}
}

TEST_CASE( "Compound Shapes - PostScript File Generation", "[CompoundShapes][PostScript]")
{
	SECTION("Rotated - PostScript File Generation")
	{
		INFO("Checking Rotated Shape - Square L=40 A=45, Triangle L=50 A=180");
		auto testSquare = Square(40);
		auto testTriangle = Triangle(50);
		auto testRotateSquare = Rotated(testSquare, 45);
		auto testRotateTriangle = Rotated(testTriangle, 180);
		test_shapePostScriptGeneration("RotatedSquareS40A45.ps", testRotateSquare);
		test_shapePostScriptGeneration("RotatedTriangleS50A180.ps", testRotateTriangle);
	}

	SECTION("Scaled - PostScript File Generation")
	{
	    INFO("Checking Scaled Shape - Square L40 X=2 Y=3, Square L40 X=10 Y=5");
	    auto testSquare = Square(40);
	    auto testScale1 = Scaled(testSquare, 2, 3);
        auto testScale2 = Scaled(testSquare, 10, 5);
        test_shapePostScriptGeneration("ScaledSquareS40X2Y3.ps", testScale1);
        test_shapePostScriptGeneration("ScaledSquareS40X10Y5.ps", testScale2);
	}

	SECTION("Layered - PostScript File Generation")
	{
	    INFO("Checking Layered Shapes - Squares L=40 L=50 L=60, Polygons 4x40 5x50 6x60");
	    auto testSquare40 = Square(40);
	    auto testSquare50 = Square(50);
	    auto testSquare60 = Square(60);
	    auto testPolygon5x50 = Polygon(5,50.0);
	    auto testPolygon8x80 = Polygon(8,80.0);
	    auto testLayeredSquares = Layered({testSquare40, testSquare50, testSquare60});
	    auto testLayeredPolygons = Layered({testSquare40, testPolygon5x50, testPolygon8x80});
        test_shapePostScriptGeneration("LayeredSquaresS40S50S60.ps", testLayeredSquares);
        test_shapePostScriptGeneration("LayeredS40PolygonS5L50PolygonS8L80.ps", testLayeredPolygons);
	}

	SECTION("Vertical - PostScript File Generation")
	{
	    INFO("Checking Vertical Shapes - Square L=40 Triangle L=50, Square L=40 Polygon 5x50, Polygons 5x50 8x80");
	    auto testSquare40 = Square(40);
	    auto testTriangle50 = Triangle(50);
	    auto testPolygon5x50 = Polygon(5, 50.0);
	    auto testPolygon8x80 = Polygon(8, 80.0);
	    auto verticalSquareTriangle = Vertical({testSquare40, testTriangle50});
	    auto verticalSquarePolygon = Vertical({testSquare40, testPolygon5x50});
	    auto verticalPolygons = Vertical({testPolygon5x50, testPolygon8x80});
	    test_shapePostScriptGeneration("VerticalSquareS40TriangleS50.ps", verticalSquareTriangle);
        test_shapePostScriptGeneration("VerticalSquareS40PolygonS5L50.ps", verticalSquarePolygon);
        test_shapePostScriptGeneration("VerticalPolygonS5L50PolygonS8L80.ps", verticalPolygons);
	}

	SECTION("Horizontal - PostScript File Generation")
	{}
}
