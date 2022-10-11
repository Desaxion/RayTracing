//
//  Functions.h
//  RayTracing
//
//  Created by Johan Arlinger on 2022-10-07.
//
#include "Def.h"


#ifndef Functions_h
#define Functions_h

double euclideanDistance(dvec4 _p1, dvec4 _p2){
    double x = _p1.x - _p2.x;
    double y = _p1.y - _p2.y;
    double z = _p1.z - _p2.z;
    return sqrt(x*x + y*y + z*z);
}


#endif /* Functions_h */
