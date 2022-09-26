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
        normDirection = glm::normalize((dvec3(_end.x, _end.y, _end.z) - dvec3(_start.x, _start.y, _start.z)));
        direction = (dvec3(_end.x, _end.y, _end.z) - dvec3(_start.x, _start.y, _start.z));
    }
	// Starting vertex, end vertex, direction vector
	// Constructor
	Ray(dvec4 _start,dvec4 _end,dvec3 _dir);

    dvec4 getStart() const {return start;}
    
    dvec3 getVec3Start() const {return dvec3(start.x, start.y, start.z);}
    
    dvec3 getDirection() const {return (dvec3(end.x, end.y, end.z) - dvec3(start.x, start.y, start.z)); }
    
    dvec3 getNormDirection() const { return glm::normalize(dvec3(start.x,start.y,start.z) - dvec3(end.x,end.y,end.z)); }
    
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
    dvec3 normDirection;
    dvec3 direction;

	// direction från direction-klass?

};
