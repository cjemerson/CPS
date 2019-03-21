// cps_test_main.cpp
// Original Author:
//   Glenn G. Chappell
//
// Modified Authors:
//   Charles Emerson
//
// Created: 20 Mar 2019 (from da6_test_main.cpp)
// Updated: 20 Mar 2019
//
// For CS 372 Spring 2019
// Tests for Project 2 CPS: main program.
// Uses the "Catch" unit-testing framework, version 2
// Requires are defined in cps_test_suites.cpp.


// *********************************************************************
// catch.hpp
// *********************************************************************

#define CATCH_CONFIG_FAST_COMPILE
                             // Disable some features for faster compile
#define CATCH_CONFIG_RUNNER  // We write our own main
#include "catch.hpp"         // For the "Catch" unit-testing framework


// *********************************************************************
// Additional Includes for this Test Program
// *********************************************************************

#include <iostream>          // For std::cout, endl, cin


// *********************************************************************
// Helper Functions
// *********************************************************************

// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
    while (std::cin.get() != '\n') ;
}


// *********************************************************************
// Main
// *********************************************************************

// main
// Run all tests. Prompt for ENTER before exiting.
int main(int argc,
         char *argv[])
{
    const std::string tname = "CPS"
                              " - CS 372 Project 2";
                             // Printable name for this test suite
    Catch::Session session;  // Primary Catch object
    int catchresult;         // Catch return code; for return by main

    // Handle command line
    catchresult = session.applyCommandLine(argc, argv);

    if (!catchresult)  // Continue only if no command-line error
    {
        // Run test suites
        std::cout << "BEGIN tests for "
                  << tname << std::endl << std::endl;
        catchresult = session.run();
        std::cout << "END tests for "
                  << tname << std::endl << std::endl;
    }

    // Wait for user
    std::cout << "Press ENTER to quit ";
    userPause();

    // Program return value is return code from Catch
    return catchresult;
}
