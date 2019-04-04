// Utilities.h
//
// Utility functions for CPS.


#ifndef CPS_UTILITIES_H
#define CPS_UTILITIES_H


#include <fstream>
// For std::ofstream

#include <string>
// For std::string

#include "Shape.hpp"


// *********************************************************************
// Utility Functions
// *********************************************************************

std::string getPostScriptHeader();

void makePostScriptFile(const Shape & shape, const std::string &filename);

#endif //CPS_UTILITIES_H
