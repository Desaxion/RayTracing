#pragma once
#include "Shape.h"
#include "Def.h"
#include "Ray.h"
#include "Surface.h"


class Sphere : public Shape {
public:

	Sphere() { midpoint = dvec4(3.5, 0.0, 0.0, 1.0); radius = 1.0; }
	Sphere(dvec4 _inPos, double _radius, const Surface _surface) : midpoint{ _inPos }, radius{ _radius } { surface = _surface; }

	bool intersection(const Ray &_ray, dvec4& intersectionPoint) override;

	dvec3 getVec3Midpoint() { return dvec3(midpoint.x, midpoint.y, midpoint.z); }
	
	dvec3 getNormDirection() override;
	
    dvec3 getNormDirection(dvec4 _pointOnSphere) override;
    
    dvec4 getRandomPoint() override;
    
    double getArea() override;
    
private:
	dvec4 midpoint;
	double radius;
	dvec3 normal;
};

