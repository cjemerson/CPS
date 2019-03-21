# CPS (C++ to PostScript)
CS 372 Project 2 -- Michael Bilan, Bradley Morton and Charles Emerson

## Introduction
This is a Software Construction exercise in design patterns. The goal of this project is to design and implement a high-level C++ shapes-language to PostScript translator.

## Success Criteria
Success occurs when the following are implemented and tested:

### Basic Shapes
- Circle(double radius)
- Polygon(int numSides, double sideLength)
- Rectangle(double width, double height)
- Spacer(double width, double height)
- Square(double sideLength)
- Triangle(double sideLength)

### Compound Shapes
- Rotated(Shape shape, RotationAngle rotationAngle)
- Scaled(Shape shape, double xScale, double yScale)
- Layered(Shape ... shapes)
- VerticallyStackedUp(Shape ... shapes)
- HorizontallyStackedRight(Shape ... shapes)

## Steps to Compile and Run the Main Program
(This method requires CMake 2.6 or later to be installed)

1. Create a new folder in the project folder called `build`
2. Navigate into `build`
3. `cmake ..`
4. `make`
5. Run `./cps_main.out`

## Steps to Compile and Run the Testing Framework
(This method requires CMake 2.6 or later to be installed)

1. Download the Catch2 single-header [catch.hpp](https://github.com/catchorg/Catch2/releases/download/v2.6.1/catch.hpp) into the folder `include`
2. Create a new folder in the project folder called `build` (if not already created)
3. Navigate into `build`.
4. `cmake ..`
5. `make`
6. Run `./catch_tests.out`
