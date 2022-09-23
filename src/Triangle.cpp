#include "Triangle.h"

Triangle::Triangle(dvec4 _v0, dvec4 _v1, dvec4 _v2, const Surface &_surface ) {
    
    vertices = {_v0, _v1, _v2};
    surface = _surface;
    
    //Creating two vectors that are to be crossed
    direction v0v1 = vertices[1] - vertices[0];
    direction v1v2 = vertices[2] - vertices[1];
    
    //Calculating normal using cross product
    normal = glm::normalize(glm::cross(v0v1, v1v2));
    
}

//Function to intersect the triangle
bool Triangle::intersection(const Ray &_ray) const {
    dvec3 T = _ray.getStart();
    dvec3 E1 = vertices[1] - vertices[0];
    dvec3 E2 = vertices[2] - vertices[0];
    dvec3 P = glm::cross(_ray.getDirection(),E2);
    dvec3 Q = glm::cross(T, E1);
 
    double t = glm::dot(Q,E2)/glm::dot(P,E1);
    
    if(t > EPSILON) {
        return true;
    }
    return false;
}
