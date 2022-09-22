#pragma once
#include "Def.h"
#include "Surface.h"
#include <array>
#include "Ray.h"

class Triangle {
public:
    
    Triangle() = delete;
    Triangle(dvec4 _v0, dvec4 _v1, dvec4 _v2, const Surface &_surface );
    ColorDBL getColor() { surface.getColor(); }
    int getReflModel() const { return surface.getRefl(); }
    
    bool intersection(const Ray &_ray);
    
    
    
    
private:
    //Vertices are passed as vec4s, and the last item in the list is a 1.0.
    std::array<dvec4, 3> vertices;
    direction normal;
    Surface surface;
};
