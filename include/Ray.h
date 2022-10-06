#pragma once
#include "Def.h"
#include "ColorDBL.h"
//#include "Shape.h"

class Ray {
public:
	// Default constructor
	Ray() = default;

    ~Ray() {
        /*Ray* temp = this;
        while (temp->next != nullptr) {
            //Iterate to the end of the ray list
            temp = temp->next;
        }
        //Now we are at the end of the list, start deleting shit and move backwards
        while(temp->prev) {
            temp = temp->prev;
            delete temp->next;
        }
        delete temp;*/
        
    }

    Ray(dvec4 _start, dvec3 _direction) {
        //Calculating direction
        start = _start;
        normDirection = glm::normalize(_direction);
        direction = _direction;
        end = dvec4(_start.x + direction.x, _start.y+direction.y,_start.z+direction.z,1.0);
    }

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

    dvec4 getEnd() const { return end; }
    
    dvec3 getVec3Start() const {return dvec3(start.x, start.y, start.z);}

    dvec3 getVec3End() const { return dvec3(end.x, end.y, end.z); }
    
    dvec3 getDirection() const {return (dvec3(end.x, end.y, end.z) - dvec3(start.x, start.y, start.z)); }
    
    dvec3 getNormDirection() const { return glm::normalize(dvec3(end.x,end.y,end.z) - dvec3(start.x, start.y, start.z)); }

    void setNext(Ray* _ray) { next = _ray; }
    void setPrev(Ray* _ray) { prev = _ray; }
    
    Ray getNext() const {return *this->next;}
    Ray getPrev() const {return *this->prev;}
    
    void setColor(ColorDBL _color) {color = _color;}
    ColorDBL getGolor(){return color;}
    
    void bounce(dvec3 _normal, dvec4 _position);

private:

	// Pointer to the surface, on which the starting vertex is located
	//Surface* surface;

	// Pointers to the previous and next ray
	Ray* next = nullptr;
	Ray* prev = nullptr;

    
    
	// Ray color, use class ColorRGB
    

	// Var
	dvec4 start;
	dvec4 end;
    dvec3 normDirection;
    dvec3 direction;
    ColorDBL color = ColorDBL(dvec3(1.0));
    
	// direction från direction-klass?

};
