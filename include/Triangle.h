#pragma once
#include "Shape.h"
#include "Def.h"
#include "Surface.h"
#include <array>
#include "Ray.h"

class Triangle : public Shape {
public:
    
    Triangle() = delete;
    Triangle(dvec4 _v0, dvec4 _v1, dvec4 _v2, const Surface &_surface );
    
    bool intersection(Ray _ray, dvec4& intersectionPoint);
    
    dvec3 getNormDirection() override;
    
private:
    //Vertices are passed as vec4s, and the last item in the list is a 1.0.
    std::array<dvec4, 3> vertices;
    dvec3 normal;
 
};
