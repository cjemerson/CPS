// Utilities.h
//
// Utility functions for CPS.

#ifndef CPS_UTILITIES_H
#define CPS_UTILITIES_H

#include "Shape.hpp"
#include <fstream>
#include <sstream>

// *********************************************************************
// Utility Functions
// *********************************************************************

std::string getPostScriptHeader();

void makePostScriptFile(const Shape & shape, const std::string &filename);

#endif //CPS_UTILITIES_H
