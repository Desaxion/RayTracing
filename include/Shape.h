#pragma once
#include "Def.h"
#include "Ray.h"
#include "Surface.h"
class Shape {
public:

	Shape() = default;
	Shape(ColorDBL _inColor) : surface{ _inColor } {}
	virtual bool intersection(const Ray &_ray, dvec4 &intersectionPoint) = 0;

	ColorDBL getColor() const; // { return surface.getColor(); }
	int getReflModel() const; //{ return surface.getRefl(); }

	virtual dvec3 getNormDirection() = 0;
    
    virtual dvec3 getNormDirection(dvec4 _intersectionPoint) = 0;

    virtual dvec4 getRandomPoint() = 0;
    
    virtual double getArea() = 0;
    
	Ray bounce(const Ray& _ray, dvec4 position);
	

protected:
	Surface surface;
};

