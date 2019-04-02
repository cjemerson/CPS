<!-- DOCUMENTATION.md -->

# Documentation

## Index

* [Important Notes](#important-notes)
* [Shape Class](#shape-class)
* [Basic Shapes](#basic-shapes)
    * [Circle](#circle)
    * [Rectangle](#rectangle)
    * [Polygon](#polygon)
    * [Spacer](#spacer)
* [Compound Shapes](#compound-shapes)
    * [Rotated](#rotated)
    * [Scaled](#scaled)
    * [Layered](#layered)
    * [Vertical](#vertical)
    * [Horizontal](#horizontal)
* [Advanced Shapes](#advanced-shapes)
    * [Ellipse](#ellipse)
    * [Donut](#donut)

## Important Notes

Because Shapes are passed by const reference, do not delete a Shape if they are being referenced within another Shape. This means a Shape should be named and have at least the same scope as any objects which reference it.

***Do not overlap constructor calls:*** `auto layered = Layered(Circle(80.0), Rectangle(80.0, 80.0))`

The line above will compile and the object `layered` will access the deallocated Circle and Rectangle.


## Shape Class

A Shape has one inherited user-accessible public function:
* `std::string evaluatePostScript() const` - Returns a string of valid PostScript to draw the Shape on the center of a page


A derived class of Shape must define:
* `point_t getBoundingBox() const` - Returns the bounding box to affect this and other Shapes' placement
* `std::string generatePostScript(point_t center) const` - Returns a string of valid PostScript to draw the Shape at the given center point

A derived class of Shape which needs to call the protected members `getBoundingBox()` and `generatePostScript(point_t)` of other Shapes can use the public wrapper functions `getBoundingBox(ShapeKey)` and `generatePostScript(point_t, ShapeKey)`.

An Example:
```cpp
for (const auto & shape : shapes)
{
    auto boundingBox = shape.getBoundingBox({});

    point_t center = {0.0, 0.0}; 
    auto postscript = shape.generatePostScript(center, {});

    // ...
}
    
```


## Basic Shapes

### Circle

Interface: `Circle(double radius)`

Description: A circle with the given radius.

Example:
```cpp
auto circle = Circle(80.0);
```


### Rectangle

Interface: `Rectangle(double width, double height)`

Description: A rectangle with the given width and height.

Example:
```cpp
auto rectangle = Rectangle(80.0, 40.0);
```


### Square

Interface: `Square(double sideLength)`

Description: A square with the given side length.

Example:
```cpp
auto square = Square(80.0);
```


### Triangle

Interface: `Triangle(double sideLength)`

Description: A triangle with the given side length.

Example:
```cpp
auto triangle = Triangle(80.0);
```


### Polygon

Interface: `Polygon(unsigned int numSides, double sideLength)`

Description: A regular polygon with the given number of sides.

Example:
```cpp
auto polygon = Polygon(6, 40.0);
```


### Spacer

Interface: `Spacer(double width, double height)`

Description: An invisible rectangle which can offset the placement of other Shapes.

Example:
```cpp
auto spacer = Spacer(80.0, 40.0);
```


## Compound Shapes

### Rotated

Interface: `Rotated(const Shape & shape, double angleInDegrees)`

Description: Rotates a shape counter-clockwise by the given angle in degrees.

Example:
```cpp
auto rectangle = Rectangle(80.0, 40.0);
auto spacer = Rotated(rectangle, 45.0);
```


### Scaled

Interface: `Scaled(const Shape & shape, double xScale, double yScale)`

Description: Scales a shape's width and height.

Example:
```cpp
auto circle = Circle(40.0);
auto scaled = Scaled(circle, 2.0, 1.0);
```


### Layered

Interface: `Layered(std::vector<std::reference_wrapper<const Shape>> shapes)`

Description: Overlaps shapes by centering.

Example:
```cpp
auto circle = Circle(40.0);
auto scaled = Scaled(circle, 2.0, 1.0);
auto rectangle = Rectangle(80.0, 40.0);
auto layered = Layered( { circle, scaled, rectangle } );
```


### Vertical

Interface: `Vertical(std::vector<std::reference_wrapper<const Shape>> shapes)`

Description: Vertically stacks shapes from bottom to top.

Example:
```cpp
auto circle = Circle(40.0);
auto spacer = Spacer(40.0, 40.0);
auto vertical = Vertical( { circle, spacer, circle } );
```


### Horizontal

Interface: `Horizontal(std::vector<std::reference_wrapper<const Shape>> shapes)`

Description: Horizontally stacks shapes from left to right.

Example:
```cpp
auto circle = Circle(40.0);
auto spacer = Spacer(40.0, 40.0);
auto horizontal = Horizontal( { circle, spacer, circle } );
```

## Advanced Shapes

### Ellipse

Interface: `Ellipse(double xRadius, double yRadius)`

Description: An ellipse with the given x and y radii.

Example:
```cpp
auto ellipse = Ellipse(80.0, 40.0);
```


#### Donut

Interface: `Donut(unsigned int n, double offsetR, double subcircleR)`

Description: A donut-like shape with `n` evenly-distributed subcircles of radius `subcircleR` which are each centered on the radius `offsetR`.

Example:
```cpp
auto donut = Donut(100, 80.0, 40.0);
```
