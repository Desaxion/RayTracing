#pragma once
#include "Def.h"

class Ray {
public:
	// Default constructor
	Ray() = default;

    Ray(dvec4 _start, dvec4 _end) {
        //Calculating direction
		start = _start;
		end = _end;
        direction = glm::normalize((dvec3(_end.x, _end.y, _end.z) - dvec3(_start.x, _start.y, _start.z)));
    }
	// Starting vertex, end vertex, direction vector
	// Constructor
	Ray(dvec4 _start,dvec4 _end,dvec3 _dir);

    dvec4 getStart() const {return start;}
    
    dvec3 getDirection() const { return glm::normalize(start - end); }
    
private:

	// Pointer to the surface, on which the starting vertex is located
	//Surface* surface;

	// Pointers to the previous and next ray
	Ray* next;
	Ray* prev;

    
    
	// Ray color, use class ColorRGB
    

	// Var
	dvec4 start;
	dvec4 end;
    dvec3 direction;

	// direction från direction-klass?

};
