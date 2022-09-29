#pragma once
#include "Def.h"
#include "Ray.h"
#include "Surface.h"
class Shape {
public:

	Shape() = default;
	Shape(ColorDBL _inColor) : surface{ _inColor } {}
	virtual bool intersection(Ray _ray, dvec4 &intersectionPoint) = 0;

	ColorDBL getColor() const; // { return surface.getColor(); }
	int getReflModel() const; //{ return surface.getRefl(); }

	virtual dvec3 getNormDirection() = 0;
	

	Ray* bounce(Ray& _ray, dvec4 position);
	

protected:
	Surface surface;
};
