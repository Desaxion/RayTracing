#include "Triangle.h"

Triangle::Triangle(dvec4 _v0, dvec4 _v1, dvec4 _v2, const Surface& _surface) {

	vertices = { _v0, _v1, _v2 };
	surface = _surface;

	//Creating two vectors that are to be crossed
	direction v0v1 = vertices[0] - vertices[1];
	direction v1v2 = vertices[2] - vertices[1];

	//Calculating normal using cross product
	normal = glm::normalize(glm::cross(dvec3(v1v2.x,v1v2.y,v1v2.z), dvec3(v0v1.x,v0v1.y,v0v1.z)));

}

//Function to intersect the triangle
bool Triangle::intersection(const Ray &_ray, dvec4& intersectionPoint) {
	
	//Create vec3:s of all the incoming data
	/*dvec3 T = dvec3(_ray.getStart().x, _ray.getStart().y, _ray.getStart().z) - dvec3(vertices[0].x, vertices[0].y, vertices[0].z);

	dvec4 E1temp = vertices[1] - vertices[0];
	dvec4 E2temp = vertices[2] - vertices[0];

	dvec3 E1 = dvec3(E1temp.x, E1temp.y, E1temp.z);
	dvec3 E2 = dvec3(E2temp.x, E2temp.y, E2temp.z);



	dvec3 P = glm::cross(_ray.getDirection(), E2);
	dvec3 Q = glm::cross(T, E1);

	double t = glm::dot(Q, E2) / glm::dot(P, E1);

	//double u = glm::dot(P, T) / glm::dot(P, E1);
	//double v = glm::dot(Q, _ray.getDirection()) / glm::dot(P, E1);

	//if (v >= EPSILON && u >= EPSILON && (u + v <= 1)) {
		if (t > EPSILON) {
			return true;
		}
	//}
	return false;*/
    
    dvec3 E1 = dvec3(vertices[1].x, vertices[1].y, vertices[1].z ) - dvec3(vertices[0].x, vertices[0].y, vertices[0].z );
    dvec3 E2 = dvec3(vertices[2].x, vertices[2].y, vertices[2].z ) - dvec3(vertices[0].x, vertices[0].y, vertices[0].z );
    dvec3 h = glm::cross(_ray.getDirection(),E2);
    double a = glm::dot(E1,h);


    if(a > -EPSILON && a < EPSILON){ //Ray is parallel to triangle
        return false;
    }
    double f = 1.0/a;
    dvec3 s = _ray.getVec3Start() - dvec3(vertices[0].x, vertices[0].y, vertices[0].z);
    double u = f * glm::dot(s,h);
    
   // if(u < 0.0 || u > 1.0){ return false; }
    
    dvec3 q = glm::cross(s, E1);
    
    double v = f* glm::dot(_ray.getDirection(),q);
    
    if(v < 0.0 || u + v > 1.0) { return false; }
    double t = f * glm::dot(E2, q);
    if(t> EPSILON)
    {
        dvec3 temp = _ray.getVec3Start() + _ray.getDirection() * t;
        intersectionPoint = dvec4(temp.x, temp.y, temp.z, 1.0);
        return true;
    }
  

   else { return false; }
    
}

dvec3 Triangle::getNormDirection() {
    return glm::normalize(normal);
}

dvec3 Triangle::getNormDirection(dvec4 _inArg) {
    return glm::normalize(normal);
}
