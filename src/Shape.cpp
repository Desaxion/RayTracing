#include "Shape.h"
#include "Def.h"


ColorDBL Shape::getColor() const { return surface.getColor(); }
int Shape::getReflModel() const { return surface.getRefl(); }

Ray* Shape::bounce(Ray &_ray, dvec4 position) {
	//First, calculate the reflectionangle


	dvec3 newDirection(glm::reflect(_ray.getDirection(), this->getNormDirection()));
	
	//The vector is now calculated, but has to be translated to end of next vector
	//dvec4 newDirection4(dvec4(-newDirection.x, -newDirection.y, newDirection.z, 1.0));
	//vec3 tempDirection = vec3(_ray.getDirection().x, _ray.getDirection().y, _ray.getDirection().z);


	//dvec3 newTempEndPoint = dvec3(position.x + newDirection.x * _ray.getDirection().length(), position.y + newDirection.y * _ray.getDirection().length(),position.z + newDirection.z * _ray.getDirection().length());
	//dvec3 newTempEndPoint = dvec3(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z);
	
	//dvec4 newEndPoint(newTempEndPoint.x, newTempEndPoint.y, newTempEndPoint.z, 1.0);
	//Then create a new ray
	Ray* newRay = new Ray(position,newDirection);

	_ray.setNext(newRay);
	newRay->setPrev(&_ray);

	return newRay;
}