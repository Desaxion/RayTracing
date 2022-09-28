#pragma once
#include "Def.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>

class ColorDBL {
public:
    
    ColorDBL()  {
        //color = dvec3(colors[0],colors[1], colors[2]);//dvec3(randomDouble(), randomDouble(), randomDouble());*/
        color = dvec3(0.0, 0.1, 0.0);
    }

    ColorDBL(double r, double g, double b) {
        color = dvec3(r, g, b);
    }
    
    ColorDBL(dvec3 inColor) : color{ inColor } {};
    
    dvec3 getColor() const { return color; };
    void setColor(const dvec3& inColor) {color = inColor;};


private:
    double randomDouble();
    dvec3 color;
};
