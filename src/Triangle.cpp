#include "Triangle.h"

Triangle::Triangle(dvec4 _v0, dvec4 _v1, dvec4 _v2, const Surface& _surface) {

	vertices = { _v0, _v1, _v2 };
	surface = _surface;

	//Creating two vectors that are to be crossed
	direction v0v1 = vertices[1] - vertices[0];
	direction v1v2 = vertices[2] - vertices[1];

	//Calculating normal using cross product
	normal = glm::normalize(glm::cross(v0v1, v1v2));

}

//Function to intersect the triangle
bool Triangle::intersection(const Ray& _ray) const {
	
	//Create vec3:s of all the incoming data
	dvec3 T = dvec3(_ray.getStart().x, _ray.getStart().y, _ray.getStart().z) - dvec3(vertices[0].x, vertices[0].y, vertices[0].z);

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
	return false;
}
