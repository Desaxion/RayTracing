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
    
    bool intersection(const Ray& _ray, dvec4& intersectionPoint) override;
    
    dvec3 getNormDirection() override;
    
    dvec3 getNormDirection(dvec4 _inArg) override;
    
    dvec4 getRandomPoint() override;
    
    double getArea() override;
    
private:
    //Vertices are passed as vec4s, and the last item in the list is a 1.0.
    std::array<dvec4, 3> vertices;
    dvec3 normal;
 
};
