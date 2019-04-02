// main.cpp
//
// Simple main to generate shapes.


#include <iostream>
#include "BasicShapes.hpp"
#include "CompoundShapes.hpp"
#include "AdvancedShapes.hpp"
#include "Utilities.hpp"

int main(int argc, char const *argv[])
{
    auto topLBotR = Donut(12, 20.0, 40.0);
    auto mid = Donut(42, 60.0, 40.0);

    auto vertical1 = Vertical({topLBotR, mid, topLBotR});

    auto topRBotL = Donut(42, 40.0, 40.0);
    auto horizontal = Horizontal({topRBotL, vertical1, topRBotL});
    auto rotated = Rotated(horizontal, 45.0);

    makePostScriptFile(rotated, "output.ps");

	return 0;
}
