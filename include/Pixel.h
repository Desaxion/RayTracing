#pragma once
#include "Def.h"
#include "ColorDBL.h"
#include <stdlib.h> 

class Pixel {
public:
    
    Pixel() {


        double colors[3] = { 0.0, 0.0, 0.0 };
        srand(std::time(nullptr));


        colors[rand() % 3] = .5;
        color = dvec3(colors[0], colors[1], colors[2]);
    }
    
    //vec3 getColor() const {return color.getColor(); };
    void setColor(ColorDBL _color) { color = _color; }
   
    //ColorDBL color;
    
private:
    ColorDBL color;
    
    friend std::ostream& operator<<(std::ostream& os, const Pixel& p);
    
};

