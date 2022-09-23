#pragma once
#include "Def.h"

class Ray {
public:
	// Default constructor
	Ray() = default;

    Ray(dvec3 _start, dvec3 _end) {
        //Calculating direction
        direction = glm::normalize((_end - _start));
    }
	// Starting vertex, end vertex, direction vector
	// Constructor
	Ray(dvec3 _start,dvec3 _end,dvec3 _dir);

    dvec3 getStart() const {return start;}
    
    dvec3 getDirection() const { return glm::normalize(start - end); }
    
private:

	// Pointer to the surface, on which the starting vertex is located
	//Surface* surface;

	// Pointers to the previous and next ray
	Ray* next;
	Ray* prev;

    
    
	// Ray color, use class ColorRGB
    

	// Var
	dvec3 start;
	dvec3 end;
    dvec3 direction;

	// direction från direction-klass?

};
