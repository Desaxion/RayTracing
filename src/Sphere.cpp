#include "Sphere.h"

bool Sphere::intersection(Ray _ray, dvec4& intersectionPoint) {

	//Ray from spheres midpoint to the start of the ray
	dvec3 T = _ray.getVec3Start() - dvec3(midpoint.x, midpoint.y, midpoint.z);

	double p = glm::dot(_ray.getNormDirection(), T);
	double q = glm::dot(T, T) - (radius * radius);

	double discriminant = (p * p) - q;
	if (discriminant < 0.0) { //no intersection
		return false;
	}
	else { 

	//Calculating hitpoint
	float dRoot = sqrt(discriminant);
	double dist1 = abs(-p - dRoot);
	double dist2 = abs(-p + dRoot);

	//Find the entry point on the sphere
	if (dist1 > dist2) {
		intersectionPoint = dvec4(dist2 * _ray.getNormDirection().x, dist2 * _ray.getNormDirection().y, dist2 * _ray.getNormDirection().z, 1.0); //this wrong
	}
	else { intersectionPoint = dvec4(dist1 * _ray.getNormDirection().x, dist1 * _ray.getNormDirection().y, dist1 * _ray.getNormDirection().z, 1.0); }

	dvec4 tempNormal = intersectionPoint - midpoint;

	normal = glm::normalize(dvec3(tempNormal.x, tempNormal.y, tempNormal.z));

	return true;
	}

	//return (discriminant > 1e-7) ? 2 : 1;
	
}

dvec3 Sphere::getNormDirection() {
	return normal;
}