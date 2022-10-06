#include "Triangle.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <algorithm>
#include <numeric>
#include <vector>

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
//Returns a random point on the triangle
dvec4 Triangle::getRandomPoint() {
    
    dvec4 randomPointOnTriangle;
    
    //The following code generate 3 random numbers that together add up to 1, aka the barycentric coordinates.
    srand(std::time(NULL));
    std::vector<double> v(3);
    std::generate(v.begin(), v.end(), rand);
    const double total = std::accumulate(v.begin(), v.end(), 0.0);
    for (double& value: v) value /= total;

    //Translate barycentric coordinates to cartesian coordinates using following formula:
    /*
     
     X = (u * p0.x + v * p1.x + w * p2.x)
     Y = (u * p0.y + v * p1.y + w * p2.y)
     Z = (u * p0.z + v * p1.z + w * p2.z)
     
     where u, v and w are the barycentric coordinates, and p0, p1 and p2 are the vertices of the triangle
     
     */
    randomPointOnTriangle.x = vertices[0].x*v[0] + vertices[1].x*v[1] + vertices[2].x*v[2];
    randomPointOnTriangle.y = vertices[0].y*v[0] + vertices[1].y*v[1] + vertices[2].y*v[2];
    randomPointOnTriangle.z = vertices[0].z*v[0] + vertices[1].z*v[1] + vertices[2].z*v[2];
    randomPointOnTriangle.w = 1.0;
    
    return randomPointOnTriangle;
}


double Triangle::getArea() {
//Calculating area using Herons Formula:
    double area;
    double lE1, lE2, lE3;
    lE1 = euclideanDistance(vertices[0],vertices[1]);
    lE2 = euclideanDistance(vertices[1],vertices[2]);
    lE3 = euclideanDistance(vertices[2],vertices[0]);
    double s = (lE1 + lE2 + lE3)/2.0;
    area = sqrt(s*((s-lE1)*(s-lE2)*(s-lE3)));
    return area;
}
