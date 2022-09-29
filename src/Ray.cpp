#include "Ray.h"

/*
Ray* Ray::bounce(Shape* _shape) {
	//First, calculate the reflectionangle
	//dvec3 newDirection(glm::reflect(_ray.getNormDirection(), _shape->getNormDirection()));
	dvec3 newTempEndPoint(glm::reflect(this->getDirection(), _shape->getNormDirection()));
	dvec4 newEndPoint(newTempEndPoint.x, newTempEndPoint.y, newTempEndPoint.z, 1.0);
	//Then create a new ray
	Ray *newRay= new Ray(this->end, newEndPoint);
	this->next = newRay;
	newRay->prev = this;

	return newRay;
}
*/