#pragma once
#include "Shape.h"
#include "Def.h"
#include "Surface.h"
#include <array>
#include "Ray.h"
//#include "Functions.h"

class Triangle : public Shape {
public:
    
    //Triangle() = delete;
    Triangle(dvec4 _v0, dvec4 _v1, dvec4 _v2, const Surface &_surface );
    Triangle() {
        vertices = { dvec4(0.0,0.0,0.0,1.0), dvec4(1.0,0.0,0.0,1.0), dvec4(0.0,1.0,0.0,1.0) };

        //Creating two vectors that are to be crossed
        direction v0v1 = vertices[0] - vertices[1];
        direction v1v2 = vertices[2] - vertices[1];

        //Calculating normal using cross product
        normal = glm::normalize(glm::cross(dvec3(v1v2.x, v1v2.y, v1v2.z), dvec3(v0v1.x, v0v1.y, v0v1.z)));
    }
    
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
