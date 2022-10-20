#pragma once
#include "Def.h"
#include "Triangle.h"
#include <array>
class Polygon : public Triangle {
public:
    //Triangle(dvec4 _v0, dvec4 _v1, dvec4 _v2, const Surface& _surface);
    Polygon(dvec4 _position, double _height, double _width, double _angle, Surface _surface) : position{ _position }, height{ _height }, width{ _width }, angle{_angle} {
        surface = _surface;
        //This creates the bottom
        vertices[0] = dvec4(position.x + cos(angle) * width, position.y + sin(angle) * width, position.z, 1.0);

        vertices[1] = dvec4(position.x + cos(angle + (2*PI/3.0)) * width, position.y + sin(angle + (2*PI / 3.0)) * width, position.z, 1.0);

        vertices[2] = dvec4(position.x + cos(angle + (4.0*PI / 3.0)) * width, position.y + sin(angle + (4.0*PI / 3.0)) * width, position.z, 1.0);

        vertices[3] = dvec4(position.x, position.y, position.z + height, 1.0);

        sides[3] = new Triangle(vertices[0], vertices[2], vertices[1], surface);
        sides[1] = new Triangle(vertices[0], vertices[1], vertices[3], surface);
        sides[2] = new Triangle(vertices[1], vertices[2], vertices[3], surface);
        sides[0] = new Triangle(vertices[2], vertices[0], vertices[3], surface);
    }

    std::array<Triangle*, 4> sides;

private:

  std::array<dvec4, 4> vertices;

  dvec4 position;

  double height;
  double angle  = 0;
  double width;
    
  Surface surface;

};
