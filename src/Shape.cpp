#include "Shape.h"
#include "Def.h"


ColorDBL Shape::getColor() const { return surface.getColor(); }
int Shape::getReflModel() const { return surface.getRefl(); }

Ray Shape::bounce(const Ray &_ray, dvec4 position) {
	//First, calculate the reflectionangle
	dvec3 newDirection(glm::reflect(_ray.getDirection(), this->getNormDirection()));

	//Then create a new ray
	Ray newRay(position,newDirection);
    //Ray* temp = newRay;
    
	//_ray.setNext(temp);
	//newRay.setPrev(&_ray);

	return newRay;
}
