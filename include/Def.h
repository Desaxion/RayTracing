#ifndef Def
#define Def

#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

typedef glm::vec4 vec4;
typedef glm::dvec4 dvec4;
typedef glm::vec3 vec3;
typedef glm::dvec3 dvec3;
typedef glm::vec3 direction;
typedef glm::mat4 mat4;

const int DIFFUSE = 0;
const int MIRROR = 1;
const int LIGHTSOURCE = 2;
const int TRANSPARENT = 3;

const double EPSILON = 0.00001;
const double PI = 3.14159265359;

/*double euclideanDistance(dvec4 _p1, dvec4 _p2){
    double x = _p1.x - _p2.x;
    double y = _p1.y - _p2.y;
    double z = _p1.z - _p2.z;
    return sqrt(x*x + y*y + z*z);
}
*/
/*
double euclideanVectorDistance(dvec3 vec){
    return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}*/

#endif
