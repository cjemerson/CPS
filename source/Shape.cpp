// Shape.cpp
//
// Basic Shapes Source.


#include "Shape.hpp"


// *********************************************************************
// PostScript Header for Output
// *********************************************************************

std::string getPostScriptHeader(){
    return std::string(R"(%!
% output.ps
%
% Created using CPS.
% https://www.github.com/cjemerson/CPS


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Basic Shapes
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% center_x center_y radius -- (on stack)
/circle {
    newpath
        % center_x center_y on the stack
        0 360 arc
        closepath
    stroke
} def

% center_x center_y width height -- (on stack)
/rectangle {
    /h exch def
    /w exch def

    newpath
        % center_x center_y on the stack
        moveto
        w 2 div h 2 div rmoveto % top-right

        w neg 0 rlineto         % top-left
        0 h neg rlineto         % bottom-left
        w 0 rlineto             % bottom-right
        closepath
    stroke
} def

% center_x center_y sideLength numSides -- (on stack)
/polygon {
    /n exch def
    /sideLength exch def

    /sideAngle 180 n 2 sub mul n div def

    newpath
        % center_x center_y on the stack
        moveto

        % rmoveto left-most point on bottom length
        /halfSideTangent sideAngle 2 div sin sideAngle 2 div cos div def
        sideLength -2 div dup halfSideTangent mul rmoveto

        0 180 sideAngle sub 360 {
            /i exch def

            sideLength i cos mul
            sideLength i sin mul
            rlineto
        } for

    closepath
    stroke
} def


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Macros
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% center_x center_y angle
/rotateAbout {
    /angle exch def
    /y exch def
    /x exch def

    x y translate
    angle rotate
    x neg y neg translate
} def

% center_x center_y scale_x scale_y
/scaleAbout {
    /scale_y exch def
    /scale_x exch def
    /y exch def
    /x exch def

    x y translate
    scale_x scale_y scale
    x neg y neg translate
} def


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Main
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

)");
}


// *********************************************************************
// Shape Class Source
// *********************************************************************

std::string Shape::evaluatePostScript() const
{
    const point_t center = {8.5*72.0/2.0, 11.0*72.0/2.0};

    return getPostScriptHeader() + generatePostScript(center) + "\nshowpage\n";
}
