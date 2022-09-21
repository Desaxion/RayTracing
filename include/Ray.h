#pragma once
#include "Def.h"

class Ray {
public:
	// Default constructor
	Ray() = default;

	// Starting vertex, end vertex, direction vector
	// Constructor
	Ray(vec3 _start,vec3 _end,vec3 _dir);

private:

	// Pointer to the surface, on which the starting vertex is located
	//Surface* surface;

	// Pointers to the previous and next ray
	Ray* next;
	Ray* prev;

	// Ray color, use class ColorRGB


	// Var
	vec3 start;
	vec3 end;

	// direction från direction-klass?

};
