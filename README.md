# CPS (C++ to PostScript)
CS 372 Project 2 -- Michael Bilan, Bradley Morton and Charles Emerson


## Table of Contents:

1. [Introduction](#introduction)
2. [Progress](#progress)
3. [Steps to Compile and Run the Main Program](#steps-to-compile-and-run-the-main-program)
4. [Steps to Compile and Run the Testing Framework](#steps-to-compile-and-run-the-testing-framework)
5. [Documentation](#documentation)


## Introduction
This is a Software Construction exercise in design patterns. The goal of this project is to design and implement a high-level C++ shapes-language to PostScript translator.


## Progress

#### Basic Shapes
|            | Does it exist?     | Does it pass the bounding box test? | Does it pass the PostScript test? | Is it documented?  |
| :---       | :---:              | :---:                               | :---:                             | :---:              |
| Circle     | :heavy_check_mark: | :heavy_check_mark:                  | :heavy_check_mark:                | :heavy_check_mark: |
| Polygon    | :heavy_check_mark: | :heavy_check_mark:                  | :heavy_check_mark:                | :heavy_check_mark: |
| Spacer     | :heavy_check_mark: | :heavy_check_mark:                  | :heavy_check_mark:                | :heavy_check_mark: |
| Square     | :heavy_check_mark: | :x:                                 | :x:                               | :heavy_check_mark: |
| Triangle   | :heavy_check_mark: | :x:                                 | :x:                               | :heavy_check_mark: |

#### Compound Shapes
|            | Does it exist?     | Does it pass the bounding box test? | Does it pass the PostScript test? | Is it documented?  |
| :---       | :---:              | :---:                               | :---:                             | :---:              |
| Rotated    | :heavy_check_mark: | :x:                                 | :x:                               | :heavy_check_mark: |
| Scaled     | :heavy_check_mark: | :x:                                 | :x:                               | :heavy_check_mark: |
| Layered    | :heavy_check_mark: | :x:                                 | :x:                               | :heavy_check_mark: |
| Vertical   | :heavy_check_mark: | :x:                                 | :x:                               | :heavy_check_mark: |
| Horizontal | :heavy_check_mark: | :x:                                 | :x:                               | :heavy_check_mark: |

#### Advanced Shapes
|                | Does it exist? | Does it pass the bounding box test? | Does it pass the PostScript test? | Is it documented? |
| :---           | :---:          | :---:                               | :---:                             | :---:             |
| Star           | :x:            | :x:                                 | :x:                               | :x:               |
| Ellipse        | :x:            | :x:                                 | :x:                               | :x:               |
| Diamond        | :x:            | :x:                                 | :x:                               | :x:               |
| Right-Triangle | :x:            | :x:                                 | :x:                               | :x:               |


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


## Documentation
See the official [documentation](reference/DOCUMENTATION.md).
