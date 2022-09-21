#pragma once
#include "Def.h"

class ColorDBL {
public:
    
    ColorDBL()  {
        color = dvec3(0.0, 1.0, 0.0);
    }
    
    ColorDBL(dvec3 inColor) : color{ inColor } {};
    
    dvec3 getColor() const { return color; };
    void setColor(const dvec3& inColor) {color = inColor;};
    
private:
    dvec3 color;
};
