// AdvancedShapes.cpp
//
// Advanced Shapes Source.


#include "AdvancedShapes.hpp"


// *********************************************************************
// Donut class
// *********************************************************************

Donut::Donut(unsigned int numCircles, double offsetR, double subcircleR)
    : Layered({_vertical}), /* Dummy value, overwritten below */
      _maxR(std::abs(offsetR) + std::abs(subcircleR)),
      _circle(subcircleR),
      _spacer(0.0, 2.0*_maxR - 2.0*std::abs(subcircleR)),
      _vertical( {_circle, _spacer} ),
      _listOfRotated{}
{
    for (unsigned int i = 0; i < numCircles; ++i)
    {
        double angle = i * (360.0/numCircles);

        _listOfRotated.emplace_back(_vertical, angle);
    }

    std::vector<std::reference_wrapper<const Shape>> refList;
    for (const auto & rotated : _listOfRotated)
    {
        refList.emplace_back(rotated);
    }

    // Overwrite Layered constructor intialization
    _shapeReferences = std::move(refList);
}


point_t Donut::getBoundingBox() const
{
    return {2.0*_maxR, 2.0*_maxR};
}
