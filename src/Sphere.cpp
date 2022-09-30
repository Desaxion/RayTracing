#include "Sphere.h"

bool Sphere::intersection(const Ray &_ray, dvec4& intersectionPoint) {

    dvec3 rayBegin = _ray.getVec3Start();
	//Ray from spheres midpoint to the start of the ray
	dvec3 T = rayBegin - dvec3(midpoint.x, midpoint.y, midpoint.z);

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
        
        double theDistance = 0.0;

	//Find the entry point on the sphere
	if (dist1 > dist2) {
        
        //intersectionPoint = dvec4(_ray.getStart().x+ dist2 * _ray.getNormDirection().x,_ray.getStart().y + dist2 * _ray.getNormDirection().y,_ray.getStart().z + dist2 * _ray.getNormDirection().z, 1.0);
        theDistance = dist2;
		//intersectionPoint = dvec4(dist2 * _ray.getNormDirection().x,dist2 * _ray.getNormDirection().y, dist2 * _ray.getNormDirection().z, 1.0); //this wrong
	}
	else { //intersectionPoint = dvec4(_ray.getStart().x + dist1 * _ray.getNormDirection().x,_ray.getStart().y + dist1 * _ray.getNormDirection().y,_ray.getStart().z + dist1 * _ray.getNormDirection().z, 1.0); }
        //intersectionPoint = dvec4( dist2 * _ray.getNormDirection().x, dist2 * _ray.getNormDirection().y, dist2 * _ray.getNormDirection().z, 1.0);
        theDistance = dist1;
    }
        dvec3 tempVec3 = rayBegin + theDistance*_ray.getNormDirection();
        
        intersectionPoint = dvec4(tempVec3.x,tempVec3.y,tempVec3.z,1.0);
        
        
	dvec4 tempNormal = intersectionPoint - midpoint;

	normal = glm::normalize(dvec3(tempNormal.x, tempNormal.y, tempNormal.z));
       // intersectionPoint = dvec4(intersectionPoint.x + normal.x*0.1,intersectionPoint.y + normal.y*0.1,intersectionPoint.z + normal.z*0.1,1.0);
	return true;
	}

	//return (discriminant > 1e-7) ? 2 : 1;
	
}

dvec3 Sphere::getNormDirection() {
	return normal;
}

dvec3 Sphere::getNormDirection(dvec4 _pointOnSphere){
    return glm::normalize(dvec3(_pointOnSphere.x-midpoint.x,_pointOnSphere.y-midpoint.y,_pointOnSphere.z-midpoint.z));
}
